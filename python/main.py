import tkinter as tk

def getFont(size: int):
  return ('TH SarabunPSK', size)

def checkBound(score: int, minimum: int, maximum: int):
  return minimum <= score and score <= maximum

def convertScore(scoreText: str):
  try:
    score = int(scoreText)
    return score
  except:
    return False

def main():
  root = tk.Tk()
  
  # Attributes
  root.title("โปรแกรมคำนวนเกรด")
  root.resizable(False, False)

  # Components
  welcome_text = tk.Label(text="คำนวนเกรด", fg="blue", font=('TH SarabunPSK', 20, 'bold'))
  
  score_1_text = tk.Label(text="คะแนนเก็บก่อนกลางภาค (เต็ม 30 คะแนน)", font=getFont(16))
  collected_score_1 = tk.Entry(width=15)
  
  score_midterm_text = tk.Label(text="คะแนนสอบกลางภาค (เต็ม 20 คะแนน)", font=getFont(16))
  midterm_score = tk.Entry(width=15)
  
  score_2_text = tk.Label(text="คะแนนเก็บหลังกลางภาค (เต็ม 30 คะแนน)", font=getFont(16))
  collected_score_2 = tk.Entry(width=15)
  
  score_final_text = tk.Label(text="คะแนนสอบปลายภาค (เต็ม 20 คะแนน)", font=getFont(16))
  final_score = tk.Entry(width=15)

  # Function to calculate Grading
  def calculateScore():
    error_list = list()
    before_midterm = collected_score_1.get()
    score_1 = convertScore(before_midterm)
    if score_1 == False or not checkBound(score_1, 0, 30):
      error_list.append("คะแนนก่อนกลางภาค")
    midterm = midterm_score.get()
    score_2 = convertScore(midterm)
    if score_2 == False or not checkBound(score_2, 0, 20):
      error_list.append("คะแนนสอบกลางภาค")
    after_midterm = collected_score_2.get()
    score_3 = convertScore(after_midterm)
    if score_3 == False or not checkBound(score_3, 0, 30):
      error_list.append("คะแนนหลังกลางภาค")
    final = final_score.get()
    score_4 = convertScore(final)
    if score_4 == False or not checkBound(score_4, 0, 20):
      error_list.append("คะแนนสอบปลายภาค")

    response_page = tk.Toplevel(root)
    response_page.minsize(300, 100)
    response_page.title("ผลลัพธ์")
    response_page.resizable(False,False)

    if len(error_list):
      error_message = "ข้อมูลของ " + ", ".join(error_list) + " ผิดพลาด"
      print(error_message)
      
      response = tk.Label(response_page, text=error_message, font=getFont(16))
      close_button = tk.Button(response_page, text="ปิด", font=getFont(16), command=response_page.destroy)
      
      response.pack(padx=10)
      close_button.pack(padx=10, pady=5)
      return
    
    sum_score = score_1 + score_2 + score_3 + score_4
    grade = ""
    if sum_score >= 80:
      grade = "4"
    elif sum_score >= 75:
      grade = "3.5"
    elif sum_score >= 70:
      grade = "3"
    elif sum_score >= 65:
      grade = "2.5"
    elif sum_score >= 60:
      grade = "2"
    elif sum_score >= 55:
      grade = "1.5"
    elif sum_score >= 50:
      grade = "1"
    else:
      grade = "0"
    
    response_text = tk.Label(response_page, text="เกรดของคุณคือ " + grade, font=getFont(16))
    close_button = tk.Button(response_page, text="ปิด", font=getFont(16), command=response_page.destroy)
    
    response_text.pack(padx=10)
    close_button.pack(pady=5)

  calculate_button = tk.Button(text="คำนวณ", font=getFont(16), command=calculateScore)

  # Add Components to GUI
  welcome_text.pack(padx=5);
  score_1_text.pack(padx=5);
  collected_score_1.pack(padx=5);
  score_midterm_text.pack(padx=5);
  midterm_score.pack(padx=5);
  score_2_text.pack(padx=5);
  collected_score_2.pack(padx=5);
  score_final_text.pack(padx=5);
  final_score.pack(padx=5);
  calculate_button.pack(pady=10);

  # Run GUI
  root.mainloop()

if __name__ == '__main__':
  main()