import math
s= [5.142,16.344,17.150,
18.325,
22.473,
25.789,
25.928,
26.230,
29.153,
32.264,
35.138,
35.387,
41.743,
42.374,
43.388,
46.975,
47.246,
51.309,
53.628,
56.689,
60.392,
74.860,
76.610,
77.456,
93.350,
94.216,
95.831,
103.956,
111.403,
117.269,
118.441,
121.334,
122.694,
128.675,
136.434,
168.727,
172.222,
213.474,
213.889,
215.220,
221.943,
229.777,
235.789,
281.492,
351.505]
n= len(s)
print n

somma = sum (s)/n
print somma
deviazione= [0 for c in range (len(s))]
for i in range(len(s)):
    deviazione [i]=((s[i]-somma)**2) 
    
    
    i=i+1
    
s = (sum (deviazione))/(n-1)
s= math.sqrt(s)

p = s/somma
print p

if p < 1: print "ok"
else: print "fuck"


