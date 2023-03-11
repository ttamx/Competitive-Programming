/*
*	The MIT License
*
*	Copyright (c) 2010 Georgios Migdos <cyberpython@gmail.com>
*
*	Permission is hereby granted, free of charge, to any person obtaining a copy
*	of this software and associated documentation files (the "Software"), to deal
*	in the Software without restriction, including without limitation the rights
*	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*	copies of the Software, and to permit persons to whom the Software is
*	furnished to do so, subject to the following conditions:
*
*	The above copyright notice and this permission notice shall be included in
*	all copies or substantial portions of the Software.
*
*	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
*	THE SOFTWARE.
*/
#include "die.cpp"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <vector>
#include <cmath>

#define PROGRAM_NAME "Bfck"
#define VERSION_NUMBER "0.1"
#define PROGRAM_INFO_MSG "A simple Brainf*ck interpreter witten in C.\nDistributed under the terms of the MIT license.\nCopyright © 2010 Georgios Migdos.\n\nUsage:\n\tbfck <input_file>\n"

#define DATA_ARRAY_SIZE 2000010 //30KB
#define DATA_INDEX_INIT 1000000
#define EXECUTION_FINISHED_MSG "\n\n--Execution finished.--\n"
#define FILE_OPEN_FAILED_ERROR_MSG "Error opening file\n"
#define UNMATCHED_BRACKET_ERROR_MSG "Unmatched bracket.\n"

static int dataa[DATA_ARRAY_SIZE];
static int dataIndex = DATA_INDEX_INIT;
static int maxDataIndex = DATA_ARRAY_SIZE-1;
static std::vector<int> outputBuffer;
static std::string program;
static int programPtr;
static int programLength;

static void error(const char *errorMsg){
  fputs(errorMsg, stderr);
}

static void errorC(int c){
  printf("%d\n", c);
  fputc(c, stderr);
}

static void fatalError(const char *errorMsg){
  fputs(errorMsg, stderr);
  exit(EXIT_FAILURE);
}

static void msg(const char *message){
  fputs(message, stdout);
}

static void msgC(int c){
  fputc(c, stdout);
}

static void printProgramInfo(){
  fprintf(stdout, "%s version %s\n%s", PROGRAM_NAME, VERSION_NUMBER, PROGRAM_INFO_MSG);
}

static void initData(){
  int i=0;
  for(i=0; i<DATA_ARRAY_SIZE; i++){
    dataa[i] = 0;
  }
}

static int isValidCmd(int cmd){
  if ( (cmd == '>') || (cmd=='<') || (cmd=='+') || (cmd=='-') || (cmd=='.') || (cmd==',') || (cmd=='[') || (cmd==']') ){
    return 0;
  }
  return 1;
}

static int getNextCommand(){
  programPtr++;
  return program[programPtr];
}

static int incrementDataPointer(){
  if(dataIndex<maxDataIndex){
    dataIndex++;
    return 0;
  }
  return 1;
}

static int decrementDataPointer(){
  if(dataIndex>0){
    dataIndex--;
    return 0;
  }
  return 1;
}

static int incrementData(){
  dataa[dataIndex] ++;
  return 0;
}

static int decrementData(){
  dataa[dataIndex] --;
  return 0;
}

static int writeByte(){
  outputBuffer.push_back(dataa[dataIndex]);
  return 0;
}

static int findClosingBracket(int current){
  long int currentPos = current;
  long int openBrackets = 1;

  int cmd = 0;
  while((currentPos < programLength) && (openBrackets>0)){
    currentPos++;
    cmd = program[currentPos];
    if(cmd==']'){
      openBrackets--;
    }else if(cmd=='['){
      openBrackets++;
    }
  }
  if(openBrackets == 0){
    return currentPos;
  } else {
    return -1;
  }
}

static int findOpeningBracket(int current){
  long int currentPos = current;
  long int closedBrackets = 1;

  int cmd = 0;
  while((currentPos > 0) && (closedBrackets>0)){
    currentPos--;
    cmd = program[currentPos];
    if(cmd=='['){
      closedBrackets--;
    }else if(cmd==']'){
      closedBrackets++;
    }
  }
  if(closedBrackets == 0){
    return currentPos;
  } else {
    return -1;
  }
}

static int jumpZero(){
  long int matchingBracketPosition = findClosingBracket(programPtr);
  if(matchingBracketPosition == -1){
    fatalError(UNMATCHED_BRACKET_ERROR_MSG);
    return 1;
  }else{
    if(dataa[dataIndex] == 0){
      programPtr = matchingBracketPosition;
    }
  }
  return 0;
}

static int jumpBackNonZero(){
  long int matchingBracketPosition = findOpeningBracket(programPtr);
  if(matchingBracketPosition == -1){
    fatalError(UNMATCHED_BRACKET_ERROR_MSG);
    return 1;
  }else{
    if(dataa[dataIndex] != 0){
      programPtr = matchingBracketPosition;
    }
  }
  return 0;
}

static int execCommand(int cmd){
  if(isValidCmd(cmd) == 0){
    
    if(cmd == '>'){
      return incrementDataPointer();
    }else if (cmd == '<'){
      return decrementDataPointer();
    }else if (cmd == '+'){
      return incrementData();
    }else if (cmd == '-'){
      return decrementData();
    }else if (cmd == '.'){
      return writeByte();
    }else if (cmd == '['){
      return jumpZero();
    }else if (cmd == ']'){
      return jumpBackNonZero();
    }
    
  }
  return 0;
}

double cal_score(int T, int P)
{
  if(P <= T)
    return 1.0;
  if(P <= 4*T) {
    return exp(2.0/3.0 - (2.0*P)/(3.0*T));
  } else if(P <= 10*T) {
    return 0.17 - ((double)P)/100.0/T;
  } else if(P <= 1000000) {
    return 0.07;
  } else {
    return 0.0;
  }
}


int main()
{
  int T=1;
  int C=1;
  std::cin >> T >> C;
  initData();
  program = A(T,C);
  programLength = program.length();
  programPtr = -1;
  while(programPtr != programLength - 1) {
    int cmd = getNextCommand();
    if(cmd!=EOF){
      execCommand(cmd);
    }
  }
  writeByte();
  int res = outputBuffer.back();
  cout << res << '\n';
    std::cout << program << std::endl;
  if(res == C) {
    std::cout << "Pass";
    //std::cout << cal_score(T, programLength) << std::endl;
    std::cout << "Program size = " << programLength << std::endl;
  } else {
    std::cout << "Failed" << std::endl;
    std::cout << "Required: " << C << std::endl;
    std::cout << "Result: " << res << std::endl;
  }
  
  //std::cout << C << std::endl;
  //for(int i=0; i<outputBuffer.size(); i++) {
  //  std::cout << outputBuffer[i] << std::endl;
  //}
  return 0;
}

