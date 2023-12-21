import sys

file_string=''
LL=5
CPI=0
ROUTE=[]
tiles=[]
s_pos=0
depth=1

def render_file(str_in):
    global LL
    ls=''
    n=0
    for i in str_in:
        n+=1
        ls+=i
        if (0 == (n%LL)):
            print(ls)
            ls=''
    print()

def visit_tile(it):
    global tiles
    global ROUTE
    global s_pos
    global file_string
    global depth
    tiles[it]['vis']=True

    if (it == s_pos):
        tmps=''
        for j in range(len(file_string)):
            if (j+1) in ROUTE:
                curr_char='█'
            else:
                curr_char=file_string[j]
            tmps+=curr_char
        render_file(tmps)
        print(ROUTE)
        print(len(ROUTE), len(ROUTE)/2)
        return

    for ni in tiles[it]['conn']:
        if it in tiles[ni]['conn']:
            if (False == tiles[ni]['vis']):
                depth+=1
                ROUTE.append(ni)
                visit_tile(ni)
                depth-=1
                ROUTE.pop()

    tiles[it]['vis']=False
        
if __name__ == '__main__':
    sys.setrecursionlimit(1000000)
    #file_obj=open('text_day10_0.txt', 'r')
    #LL=5
    file_obj=open('text_day10_1.txt', 'r')
    LL=140
    file_con=file_obj.read()
    file_obj.close()
    file_string=''
    for c in file_con:
        if (10 != ord(c)):
            file_string+=c
    tiles=[]
    t={}
    tiles.append(t) # Dummy entry for 1-based indexing.
    n=0
    for c in file_string:
        n+=1
        if (7 == n):
            pass
        t={}
        t['vis']=False
        if ('|' == c):
            t['conn']=[(n-LL), (n+LL)]
        elif ('-' == c):
            t['conn']=[(n-1), (n+1)]
        elif ('L' == c):
            t['conn']=[(n-LL), (n+1)]
        elif ('J' == c):
            t['conn']=[(n-1), (n-LL)]
        elif ('7' == c):
            t['conn']=[(n-1), (n+LL)]
        elif ('F' == c):
            t['conn']=[(n+LL), (n+1)]
        elif ('.' == c):
            t['conn']=[]
        elif ('S' == c):
            t['conn']=[(n-1), (n+1)]
            s_pos=n
        else:
            raise Exception('Unknown char!', c)
        tiles.append(t)
    ROUTE.append(s_pos+1)
    tiles[s_pos+1]['conn']=[s_pos+1-LL]
    tiles[s_pos+1]['vis']=True
    visit_tile(s_pos+1)
