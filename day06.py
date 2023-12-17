

if __name__ == '__main__':
    #file_obj=open('text_day06_0.txt', 'r')
    file_obj=open('text_day06_1.txt', 'r')
    file_con=file_obj.read()
    file_obj.close()
    file_lin=str(file_con).splitlines()
    tp=str(file_lin[0]).split(':')[1]
    tp=str(tp).split(' ')
    durations=[]
    for i in tp:
        if (0 < len(i)):
            durations.append(int(i))
    tp=str(file_lin[1]).split(':')[1]
    tp=str(tp).split(' ')
    records=[]
    for i in tp:
        if (0 < len(i)):
            records.append(int(i))
    winners=[]
    for i in range(len(durations)):
        curr_duration=durations[i]
        curr_record=records[i]
        win_cnt=0
        for h in range(curr_duration+1):
            d=(curr_duration - h) * h
            if (d > curr_record):
                win_cnt+=1
        winners.append(win_cnt)
    res=1
    for i in winners:
        res*=i
    print()
    print('Part 1:', res)
    print()
    tp=str(file_lin[0]).split(':')[1]
    tp=str(tp).split(' ')
    durations=''
    for i in tp:
        if (0 < len(i)):
            durations+=i
    durations=int(durations)
    tp=str(file_lin[1]).split(':')[1]
    tp=str(tp).split(' ')
    records=''
    for i in tp:
        if (0 < len(i)):
            records+=i
    records=int(records)

    win_cnt=0
    for h in range(durations+1):
        d=(durations - h) * h
        if (d > records):
            win_cnt+=1
    print()
    print('Part 2:', win_cnt)
    print()