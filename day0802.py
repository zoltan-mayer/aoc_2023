
graph={}
INST=''

def get_inst_gen():
    global INST
    while (True):
        for i in INST:
            yield i

inst_gen=get_inst_gen()

class Ghost():
    def __init__(self, start_nod):
        self.curr_nod=start_nod

    def take_step(self, dr):
        global graph
        next_nod=graph[self.curr_nod][dr]
        self.curr_nod=next_nod
        return str(self.curr_nod).endswith('Z')

if __name__ == '__main__':
    #file_obj=open('text_day08_0.txt', 'r')
    #file_obj=open('text_day08_1.txt', 'r')
    file_obj=open('text_day08_2.txt', 'r')
    #file_obj=open('text_day08_3.txt', 'r')
    file_con=file_obj.read()
    file_obj.close()
    file_lin=str(file_con).splitlines()
    INST=[]
    for i in file_lin[0]:
        if ('L' == i):
            INST.append(0)
        else:
            INST.append(1)
    file_lin=file_lin[2:]
    graph={}
    for i in file_lin:
        gnode=[]
        nam=str(i).split(' = ')[0]
        tp=str(i).split('= (')[1]
        tp=str(tp).split(')')[0]
        gnode.append(str(tp).split(', ')[0])
        gnode.append(str(tp).split(', ')[1])
        if (nam == gnode[0]) and (nam == gnode[1]):
            print(i)
        graph[nam]=gnode
    gh_cnt=0
    gh_lst=[]
    for i in graph:
        if str(i).endswith('A'):
            gh_lst.append(Ghost(i))
            gh_cnt+=1
    n=0
    done_cnt=0
    for i in inst_gen:
        done_cnt=0
        n+=1
        for k in gh_lst:
            ret=k.take_step(i)
            if (True == ret):
                done_cnt+=1
        if (0 == (n%1000000)):
            print(n)
        if (done_cnt == gh_cnt):
            break
    print()
    print('Part 2:', n)
    print()
