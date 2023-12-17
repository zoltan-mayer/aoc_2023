
PAKLI={}
PAKLI['A']=13
PAKLI['K']=12
PAKLI['Q']=11
PAKLI['T']=10
PAKLI['9']=9
PAKLI['8']=8
PAKLI['7']=7
PAKLI['6']=6
PAKLI['5']=5
PAKLI['4']=4
PAKLI['3']=3
PAKLI['2']=2
PAKLI['J']=1

KOMBO={}
KOMBO['5of']=7
KOMBO['4of']=6
KOMBO['full']=5
KOMBO['3of']=4
KOMBO['2pair']=3
KOMBO['1pair']=2
KOMBO['hi']=1

class CHand():
    def __init__(self, hcstr, hbid):
        self.cstr=hcstr
        self.bid=hbid
        self.cards=[]
        self.unord_cards=[]
        for c in hcstr:
            self.cards.append(PAKLI[c])
            self.unord_cards.append(PAKLI[c])
        self.cards.sort()
        kchng=-1
        streak=0
        max_s=0
        for i in range(len(self.cards)):
            if (i > 0):
                prev_card=self.cards[i-1]
            else:
                prev_card=-1
            curr_card=self.cards[i]
            if (curr_card != prev_card) or (curr_card == 1): # 'J' shall not increase strength here.
                streak=0
                kchng+=1
            else:
                streak+=1
            if (streak > max_s):
                max_s=streak
        self.htype=KOMBO['hi']
        if (0 == kchng):
            self.htype=KOMBO['5of']
        elif (1 == kchng):
            if (3 == max_s):
                self.htype=KOMBO['4of']
            else:
                self.htype=KOMBO['full']
        elif (2 == kchng):
            if (2 == max_s):
                self.htype=KOMBO['3of']
            else:
                self.htype=KOMBO['2pair']
        elif (3 == kchng):
            self.htype=KOMBO['1pair']
        else:
            self.htype=KOMBO['hi']
        ################################
        j_cnt=self.cstr.count('J')
        if (self.htype < KOMBO['5of']):
            while (j_cnt > 0):
                if (KOMBO['1pair'] == self.htype) or (KOMBO['2pair'] == self.htype) or (KOMBO['3of'] == self.htype):
                    self.htype+=2
                else:
                    self.htype+=1
                if (self.htype == KOMBO['5of']):
                    break
                j_cnt-=1

    def __lt__(self, other):
        if (self.htype == other.htype):
            for i in range(len(self.cards)):
                tc=self.unord_cards[i]
                oc=other.unord_cards[i]
                if (tc == oc):
                    continue
                else:
                    return tc < oc
        else:
            return self.htype < other.htype

if __name__ == '__main__':
    #file_obj=open('text_day07_0.txt', 'r')
    file_obj=open('text_day07_1.txt', 'r')
    file_con=file_obj.read()
    file_obj.close()
    file_lin=str(file_con).splitlines()
    all_hands=[]
    for i in file_lin:
        all_hands.append(CHand(str(i).split(' ')[0], int(str(i).split(' ')[1])))
    all_hands.sort()
    r=1
    res=0
    for i in all_hands:
        # jstr=''
        # if ('J' in i.cstr):
        #     jstr='  %d' % i.cstr.count('J')
        # print(('%6d' % r), i.cstr, i.htype, ('%4d' % i.bid), jstr)
        res+=(i.bid * r)
        r+=1
    print()
    print('Part 2:', res)
    print()
