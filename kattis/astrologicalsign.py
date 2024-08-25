a=["","Aries","Taurus","Gemini","Cancer","Leo","Virgo","Libra","Scorpio","Sagittarius","Capricorn","Aquarius","Pisces","Aries","Taurus","Gemini","Cancer","Leo","Virgo","Libra","Scorpio","Sagittarius","Capricorn","Aquarius","Pisces"]
t=int(input())
for _ in range(t):
    d,m=input().split()
    d=int(d)
    if m=="Jan":
        print(a[10+(d>=21)])
    elif m=="Feb":
        print(a[11+(d>=20)])
    elif m=="Mar":
        print(a[12+(d>=21)])
    elif m=="Apr":
        print(a[13+(d>=21)])
    elif m=="May":
        print(a[14+(d>=21)])
    elif m=="Jun":
        print(a[15+(d>=22)])
    elif m=="Jul":
        print(a[16+(d>=23)])
    elif m=="Aug":
        print(a[17+(d>=23)])
    elif m=="Sep":
        print(a[18+(d>=22)])
    elif m=="Oct":
        print(a[19+(d>=23)])
    elif m=="Nov":
        print(a[20+(d>=23)])
    elif m=="Dec":
        print(a[21+(d>=22)])
    else:
        exit(1)