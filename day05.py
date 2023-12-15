from operator import itemgetter

def get_overlap(r1, r2):
    res=False
    ret={}
    if (r2['start'] >= r1['start']):
        ret['start']=r2['start']
        ret['stop']=min([r1['stop'], r2['stop']])
        if (ret['start'] < ret['stop']):
            ret['shift']=r2['shift']
            res=True
    else:
        ret['start']=r1['start']
        if (r2['stop'] > r1['start']):
            ret['stop']=min([r1['stop'], r2['stop']])
            if (ret['start'] < ret['stop']):
                ret['shift']=r2['shift']
                res=True
    if (False == res):
        ret={}
    return (res, ret)

stages=[]
min_val=999999999999

def process_stages(sidx, prange):
    global stages
    global min_val
    if (sidx == len(stages)):
        if (prange['start'] < min_val):
            min_val=prange['start']
        return
    curr_ranges=stages[sidx]
    for r in curr_ranges:
        (res, ret) = get_overlap(prange, r)
        if (True == res):
            cv={}
            cv['start']=ret['start'] + ret['shift']
            cv['stop']=ret['stop'] + ret['shift']
            cv['shift']=0
            process_stages(sidx+1, cv)

def main():
    global stages
    global min_val
    #file_obj=open('text_day05_0.txt', 'r')
    file_obj=open('text_day05_1.txt', 'r')
    file_con=file_obj.read()
    file_obj.close()
    file_lin=str(file_con).splitlines()
    seeds=[]
    sd_parts=str(file_lin[0]).split(' ')
    i=1
    while (i < (len(sd_parts) - 1)):
        r_start=int(sd_parts[i])
        r_stop=r_start + int(sd_parts[i+1]) - 1
        cs={}
        cs['start']=r_start
        cs['stop']=r_stop
        cs['shift']=0
        seeds.append(cs)
        i+=2
    seeds=sorted(seeds, key=itemgetter('start'))
    stages=[]
    curr_stage=[]
    for idx in range(2, len(file_lin)):
        curr_lin=file_lin[idx]
        if (str(curr_lin).endswith('map:')):
            continue
        if (0 == len(curr_lin)):
            if (0 < len(curr_stage)):
                curr_stage=sorted(curr_stage, key=itemgetter('start'))
                lowest_start=curr_stage[0]['start']
                if (0 < lowest_start):
                    cs={}
                    cs['start']=0
                    cs['stop']=lowest_start-1
                    cs['shift']=0
                    curr_stage = [cs] + curr_stage
                cs={}
                cs['start']=curr_stage[-1]['stop']+1
                cs['stop']=999999999999
                cs['shift']=0
                curr_stage.append(cs)
                stages.append(curr_stage)
                curr_stage=[]
        else:
            curr_parts=str(curr_lin).split(' ')
            r_start=int(curr_parts[1])
            r_stop=r_start + int(curr_parts[2]) - 1
            r_val=int(curr_parts[0])-r_start
            cs={}
            cs['start']=r_start
            cs['stop']=r_stop
            cs['shift']=r_val
            curr_stage.append(cs)
    if (0 < len(curr_stage)):
        curr_stage=sorted(curr_stage, key=itemgetter('start'))
        lowest_start=curr_stage[0]['start']
        if (0 < lowest_start):
            cs={}
            cs['start']=0
            cs['stop']=lowest_start-1
            cs['shift']=0
            curr_stage = [cs] + curr_stage
        cs={}
        cs['start']=curr_stage[-1]['stop']+1
        cs['stop']=999999999999
        cs['shift']=0
        curr_stage.append(cs)
        stages.append(curr_stage)
        curr_stage=[]

    for i in seeds:
        process_stages(0, i)

    print(min_val)


if __name__ == '__main__':
    main()
