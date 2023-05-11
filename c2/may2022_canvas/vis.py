from matplotlib import pyplot as plt
from matplotlib.widgets import Button
import argparse

parser = argparse.ArgumentParser(
    description='Visualizator for task canvas.')
parser.add_argument('input', help='input file')

args = parser.parse_args()

fig, ax = plt.subplots()
plt.subplots_adjust(bottom=0.2)

######
# Copied from https://stackoverflow.com/a/20677983


def line_intersection(line1, line2):
    line1 = (line1[0].x, line1[0].y), (line1[1].x, line1[1].y)
    line2 = (line2[0].x, line2[0].y), (line2[1].x, line2[1].y)
    xdiff = (line1[0][0] - line1[1][0], line2[0][0] - line2[1][0])
    ydiff = (line1[0][1] - line1[1][1], line2[0][1] - line2[1][1])

    def det(a, b):
        return a[0] * b[1] - a[1] * b[0]

    div = det(xdiff, ydiff)
    if div == 0:
        raise Exception('lines do not intersect')

    d = (det(*line1), det(*line2))
    x = det(d, xdiff) / div
    y = det(d, ydiff) / div
    return x, y
######

######
# Copied from https://stackoverflow.com/a/59582674


def circle_line_segment_intersection(circle_center, circle_radius, pt1, pt2, full_line=True, tangent_tol=1e-9):
    """ Find the points at which a circle intersects a line-segment.  This can happen at 0, 1, or 2 points.

    :param circle_center: The (x, y) location of the circle center
    :param circle_radius: The radius of the circle
    :param pt1: The (x, y) location of the first point of the segment
    :param pt2: The (x, y) location of the second point of the segment
    :param full_line: True to find intersections along full line - not just in the segment.  False will just return intersections within the segment.
    :param tangent_tol: Numerical tolerance at which we decide the intersections are close enough to consider it a tangent
    :return Sequence[Tuple[float, float]]: A list of length 0, 1, or 2, where each element is a point at which the circle intercepts a line segment.

    Note: We follow: http://mathworld.wolfram.com/Circle-LineIntersection.html
    """

    (p1x, p1y), (p2x, p2y), (cx, cy) = pt1, pt2, circle_center
    (x1, y1), (x2, y2) = (p1x - cx, p1y - cy), (p2x - cx, p2y - cy)
    dx, dy = (x2 - x1), (y2 - y1)
    dr = (dx ** 2 + dy ** 2)**.5
    big_d = x1 * y2 - x2 * y1
    discriminant = circle_radius ** 2 * dr ** 2 - big_d ** 2

    if discriminant < 0:  # No intersection between circle and line
        return []
    else:  # There may be 0, 1, or 2 intersections with the segment
        intersections = [
            (cx + (big_d * dy + sign * (-1 if dy < 0 else 1) * dx * discriminant**.5) / dr ** 2,
             cy + (-big_d * dx + sign * abs(dy) * discriminant**.5) / dr ** 2)
            for sign in ((1, -1) if dy < 0 else (-1, 1))]  # This makes sure the order along the segment is correct
        if not full_line:  # If only considering the segment, filter out intersections that do not fall within the segment
            fraction_along_segment = [
                (xi - p1x) / dx if abs(dx) > abs(dy) else (yi - p1y) / dy for xi, yi in intersections]
            intersections = [pt for pt, frac in zip(
                intersections, fraction_along_segment) if 0 <= frac <= 1]
        # If line is tangent to circle, return just one point (as both intersections have same location)
        if len(intersections) == 2 and abs(discriminant) <= tangent_tol:
            return [intersections[0]]
        else:
            return intersections
######

######
# Copied from https://stackoverflow.com/a/55817881


def get_intersections(x0, y0, r0, x1, y1, r1):
    # circle 1: (x0, y0), radius r0
    # circle 2: (x1, y1), radius r1

    d = ((x1-x0)**2 + (y1-y0)**2)**0.5

    # non intersecting
    if d > r0 + r1:
        return None
    # One circle within other
    if d < abs(r0-r1):
        return None
    # coincident circles
    if d == 0 and r0 == r1:
        return None
    else:
        a = (r0**2-r1**2+d**2)/(2*d)
        h = (r0**2-a**2)**0.5
        x2 = x0+a*(x1-x0)/d
        y2 = y0+a*(y1-y0)/d
        x3 = x2+h*(y1-y0)/d
        y3 = y2-h*(x1-x0)/d

        x4 = x2-h*(y1-y0)/d
        y4 = y2+h*(x1-x0)/d

        return [(x3, y3), (x4, y4)]
######


class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def intersection(obj1, obj2, idx=None):
        if isinstance(obj1, Line) and isinstance(obj2, Line):
            # L-L intersection
            return Point(*line_intersection((obj1.p1, obj1.p2), (obj2.p1, obj2.p2)))
        elif (isinstance(obj1, Line) and isinstance(obj2, Circle)) or (isinstance(obj1, Circle) and isinstance(obj2, Line)):
            # L-C intersection
            if idx is None:
                raise ValueError('idx is None')
            if isinstance(obj1, Circle) and isinstance(obj2, Line):
                obj1, obj2 = obj2, obj1
            ret = sorted(circle_line_segment_intersection((obj2.p1.x, obj2.p1.y),
                                                          obj2.radius(),
                                                          (obj1.p1.x, obj1.p1.y),
                                                          (obj1.p2.x, obj1.p2.y),
                                                          True))[idx]
            return Point(ret[0], ret[1])
        elif isinstance(obj1, Circle) and isinstance(obj2, Circle):
            # C-C intersection
            if idx is None:
                raise ValueError('idx is None')
            ret = sorted(get_intersections(obj1.p1.x, obj1.p1.y, obj1.radius(),
                                           obj2.p1.x, obj2.p1.y, obj2.radius()))[idx]
            return Point(ret[0], ret[1])

    def plot(self, name):
        plt.scatter([self.x], [self.y], label=name)
        plt.text(self.x, self.y, name)


class Line:
    def __init__(self, p1, p2):
        if not isinstance(p1, Point) or not isinstance(p2, Point):
            raise TypeError(
                'cannot construct a line with arguments of wrong type')
        self.p1 = p1
        self.p2 = p2

    def plot(self, name):
        plt.plot([self.p1.x, self.p2.x], [self.p1.y, self.p2.y], label=name)
        plt.text((self.p1.x+self.p2.x)/2,
                 (self.p1.y+self.p2.y)/2, name, va='top')


class Circle:
    def __init__(self, p1, p2):
        if not isinstance(p1, Point) or not isinstance(p2, Point):
            raise TypeError(
                'cannot construct a circle with arguments of wrong type')
        self.p1 = p1
        self.p2 = p2

    def radius(self):
        return ((self.p2.y - self.p1.y)**2 +
                (self.p2.x - self.p1.x)**2)**0.5

    def plot(self, name):
        plt.gca().add_patch(plt.Circle((self.p1.x, self.p1.y),
                                       self.radius(), fill=False, label=name))
        plt.text(self.p1.x, self.p1.y, name, va='bottom')


class Store:
    def __init__(self):
        self.points = {0: Point(0, 0), 1: Point(0, 1)}
        self.lines = {}
        self.circles = {}
        self.last = None
        self.lastcmd = ''

    def get(self, identifier):
        if identifier[0] not in 'PLC':
            raise ValueError(f'identifier {identifier} not recognized')
        name = int(identifier[1:])
        if identifier[0] == 'P':
            return self.points[name]
        elif identifier[0] == 'L':
            return self.lines[name]
        elif identifier[0] == 'C':
            return self.circles[name]

    def set(self, identifier, item, lastcmd):
        if identifier[0] not in 'PLC':
            raise ValueError(f'identifier {identifier} not recognized')
        name = int(identifier[1:])
        if identifier[0] == 'P':
            self.points[name] = item
        elif identifier[0] == 'L':
            self.lines[name] = item
        elif identifier[0] == 'C':
            self.circles[name] = item
        self.last = (item, identifier)
        self.lastcmd = lastcmd

    def parse_operations(self, operations):
        if len(operations) == 0:
            raise ValueError(f'command not found in the current operation')
        command = operations[0]
        if command not in ['COM', 'LIN', 'INT']:
            raise ValueError(f'command {command} not recognized')
        if command == 'COM':
            return Circle(self.get(operations[1]), self.get(operations[2]))
        elif command == 'LIN':
            return Line(self.get(operations[1]), self.get(operations[2]))
        elif command == 'INT':
            if len(operations) == 4:
                return Point.intersection(self.get(operations[1]), self.get(operations[2]), int(operations[3]))
            else:
                return Point.intersection(self.get(operations[1]), self.get(operations[2]))

    def plot(self):
        for k, v in self.points.items():
            v.plot('')
        for k, v in self.lines.items():
            v.plot('')
        for k, v in self.circles.items():
            v.plot('')
        if self.last is not None:
            self.last[0].plot(self.last[1])
        plt.gca().set_aspect('equal')

    def copy(self):
        cloned = Store()
        cloned.points = self.points.copy()
        cloned.lines = self.lines.copy()
        cloned.circles = self.circles.copy()
        cloned.last = self.last
        cloned.lastcmd = self.lastcmd
        return cloned


stores = [Store()]

cmdnum = 1
with open(args.input, 'r') as f:
    for line in f:
        tokens = line.split()
        if len(tokens) == 0:
            continue
        if tokens[0] == '#':
            continue
        elif tokens[0] == '!!':
            ans = stores[-1].get(tokens[1])
            print(ans.x, ans.y)
        elif tokens[0][0] in 'PLC':
            print(f'[{cmdnum}]: {line.strip()}')
            item = stores[-1].parse_operations(tokens[1:])
            stores.append(stores[-1].copy())
            stores[-1].set(tokens[0], item, line.strip())
            cmdnum += 1
        else:
            raise ValueError(f'command {tokens[0]} not recognized')


class Index:
    def __init__(self, stores):
        self.ind = -1
        self.stores = stores
        self.xlim = self.ylim = None

    def next(self, event):
        if self.ind+1 < len(stores):
            self.ind += 1
        self.plot()

    def prev(self, event):
        if self.ind-1 >= 0:
            self.ind -= 1
        self.plot()

    def plot(self):
        ax.cla()
        plt.sca(ax)
        plt.title(f'[{self.ind}]: {self.stores[self.ind].lastcmd}')
        if self.xlim is not None and self.ylim is not None:
            plt.xlim(self.xlim)
            plt.ylim(self.ylim)
        self.stores[self.ind].plot()
        plt.draw()


callback = Index(stores)
callback.plot()
callback.xlim = plt.xlim()
callback.ylim = plt.ylim()
callback.ind = 0
callback.plot()
axprev = plt.axes([0.7, 0.05, 0.1, 0.075])
axnext = plt.axes([0.81, 0.05, 0.1, 0.075])
bnext = Button(axnext, 'Next')
bnext.on_clicked(callback.next)
bprev = Button(axprev, 'Previous')
bprev.on_clicked(callback.prev)
plt.show()
