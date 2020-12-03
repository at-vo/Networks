from math import log2

var =   [   (4,1,3),
            (6,2,4)        
        ]

var =   [   (3,1,2),
            (5,1,4),        
            (2,1,1)
        ]

var =   [   (3,1,2),
            (3,1,2),        
            (3,0,3),
            (1,0,1)
        ]


calc = 0
for c in var:
    if c[1] == 0:
        c1 = 0
    else:
        c1 = -c[0]/10 * ( (c[1]/c[0]) * log2(c[1]/c[0]) + (c[2]/c[0]) * log2(c[2]/c[0]))
    calc+=c1

print(calc)