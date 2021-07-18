#2

import datetime

def main():
    # YOUR CODE GOES HERE
    # Please take input and print output to standard input/output (stdin/stdout)
    # E.g. 'input()/raw_input()' for input & 'print' for output
    n = int(input())
    book_dict = dict()
    
    for x in range(n):
        start_date, end_date = input().strip().split(" ")
        start_date = datetime.datetime(*[int(x) for x in start_date.split("-")])
        end_date = datetime.datetime(*[int(x) for x in end_date.split("-")])
        
        while start_date < end_date:
            addDict(book_dict, start_date.strftime("%Y-%m-%d"))
            start_date += datetime.timedelta(days=1)
        
    findMaxValueFromDict(book_dict)
        
    return 0
    
def addDict(book_dict, datetime):
    if datetime in book_dict:
        book_dict[datetime] += 1
    else:
        book_dict[datetime] = 1

def findMaxValueFromDict(book_dict):
    max_value = 0
    max_name = ""
    
    for key in sorted (book_dict.keys()):
        if book_dict[key] > max_value:
            max_name = key
            max_value = book_dict[key]
            
    print(max_name)

if __name__ == '__main__':
    main()