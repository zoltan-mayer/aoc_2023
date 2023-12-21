
def process_arr(ain):
    allz=True
    for j in ain:
        if (j != 0):
            allz=False
            break
    if (True == allz):
        return 0
    ret=[]
    for i in range(1, len(ain)):
        ret.append(ain[i]-ain[i-1])
    return (ain[-1] + process_arr(ret))

if __name__ == '__main__':
    #file_obj=open('text_day09_0.txt', 'r')
    file_obj=open('text_day09_1.txt', 'r')
    file_con=file_obj.read()
    file_obj.close()
    file_lin=str(file_con).splitlines()
    res=[]
    for l in file_lin:
        if (0 < len(l)):
            ia=[int(p) for p in str(l).split(' ')]
            res.append(process_arr(ia))
    print()
    print('Part 1:', sum(res))
    print()
    res=[]
    for l in file_lin:
        if (0 < len(l)):
            ia=[int(p) for p in str(l).split(' ')]
            ia=ia[::-1]
            res.append(process_arr(ia))
    print()
    print('Part 2:', sum(res))
    print()