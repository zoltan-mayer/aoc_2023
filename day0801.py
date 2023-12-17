
INST=''

def get_inst_gen():
    global INST
    while (True):
        for i in INST:
            yield i

inst_gen=get_inst_gen()

if __name__ == '__main__':
    #file_obj=open('text_day08_0.txt', 'r')
    #file_obj=open('text_day08_1.txt', 'r')
    file_obj=open('text_day08_2.txt', 'r')
    file_con=file_obj.read()
    file_obj.close()
    file_lin=str(file_con).splitlines()
    INST=file_lin[0]
    file_lin=file_lin[2:]
    graph={}
    for i in file_lin:
        gnode={}
        nam=str(i).split(' = ')[0]
        tp=str(i).split('= (')[1]
        tp=str(tp).split(')')[0]
        gnode['left']=str(tp).split(', ')[0]
        gnode['right']=str(tp).split(', ')[1]
        graph[nam]=gnode
    n=0
    curr_nod='AAA'
    for i in inst_gen:
        n+=1
        if ('L' == i):
            next_nod=graph[curr_nod]['left']
        else:
            next_nod=graph[curr_nod]['right']
        if ('ZZZ' == next_nod):
            break
        curr_nod=next_nod
    print()
    print('Part 1:', n)
    print()
