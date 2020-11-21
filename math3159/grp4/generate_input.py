import random
import sys
from random import randrange

list_of_primes = [33554467, 33554473, 33554501, 33554503, 
                  33554509, 33554519, 33554527, 33554579, 
                  33554581, 33554593, 33554639, 33554641, 
                  33554693, 33554699, 33554737, 33554743, 
                  33554761, 33554771, 33554789, 33554831, 
                  33554839, 33554849, 33554867, 33554891, 
                  33554903, 33554929, 33554951, 33554959, 
                  33554971, 33554977, 33554993, 33555019, 
                  33555037, 33555061, 33555073, 33555077, 
                  33555079, 33555089, 33555101, 33555131, 
                  33555149, 33555163, 33555167, 33555191, 
                  33555199, 33555209, 33555217, 33555241, 
                  33555251, 33555259, 33555271, 33555281, 
                  33555283, 33555287, 33555289, 33555293, 
                  33555317, 33555341, 33555373, 33555377, 
                  33555383, 33555391, 33555397, 33555419, 
                  33555421, 33555439, 33555449, 33555461, 
                  33555469, 33555481, 33555493, 33555497, 
                  33555499, 33555517, 33555527, 33555553, 
                  33555563, 33555583, 33555611, 33555617, 
                  33555629, 33555647, 33555659, 33555661, 
                  33555667, 33555679, 33555701, 33555703, 
                  33555727, 33555737, 33555751, 33555757, 
                  33555799, 33555817, 33555853, 33555859, 
                  33555883, 33555901, 33555913, 33555931]

primitive_roots = [32, 100000, 32, 7776, 
                   32, 161051, 7776, 32, 
                   32, 100000, 1419857, 161051, 
                   32, 32, 100000, 7776, 
                   371293, 32, 32, 16807, 
                   243, 243, 32, 32, 
                   3125, 1419857, 161051, 7776, 
                   32, 3125, 243, 161051, 
                   3125, 7776, 16807, 32, 
                   243, 243, 32, 7776, 
                   16807, 243, 3125, 371293, 
                   7776, 243, 3125, 371293, 
                   7776, 32, 243, 7776, 
                   32, 3125, 16807, 32, 
                   32, 243, 3125, 243, 
                   16807, 7776, 32, 32, 
                   1419857, 7776, 243, 32, 
                   32, 28629151, 32, 243, 
                   32, 32, 3125, 16807, 
                   32, 7776, 32, 243, 
                   32, 3125, 32, 16807, 
                   32, 243, 32, 243, 
                   3125, 243, 243, 3125, 
                   7776, 3125, 32, 100000, 
                   32, 100000, 3125, 243]

values_of_A = [33554432, 13424108, 1048576, 26911673, 
               32768, 31758859, 18952252, 33554432, 
               33554432, 19665155, 14747562, 33241749, 
               32768, 32768, 688374, 26911433, 
               13053949, 32768, 33554432, 22691077, 
               30635984, 30634954, 1024, 1048576, 
               1622332, 20706408, 3509430, 12899068, 
               32768, 16104032, 30620122, 32949933, 
               23437222, 26911115, 7608424, 1024, 
               59049, 14348907, 1048576, 26911045, 
               500068, 59049, 12841909, 11920105, 
               9536188, 14348907, 15885872, 13561821, 
               31262136, 1024, 30591488, 20987321, 
               33554432, 15822242, 13604211, 1024, 
               33554432, 14348907, 15744068, 14348907, 
               11701571, 23024152, 32768, 33554432, 
               18714545, 19365238, 14348907, 1024, 
               1024, 20035556, 32768, 59049, 
               1048576, 1024, 12514351, 14030825, 
               33554432, 7707241, 1048576, 14348907, 
               1048576, 15495002, 1048576, 5924680, 
               1048576, 7714693, 1048576, 30546992, 
               19606423, 14348907, 30542048, 9765625, 
               20947149, 9765625, 1024, 13616080, 
               33554432, 23848683, 29098177, 59049]

S1 = [18170831, 11338665, 13986594, 13958166, 
      27961194, 8900507, 24487120, 24539544, 
      13847326, 20121038, 17110226, 1116247, 
      25308433, 2043221, 18767119, 31675561, 
      33347917, 3525560, 23177813, 6468140, 
      1554101, 8748920, 9250776, 14962679, 
      15616434, 18967513, 27463954, 29632605, 
      17600013, 16176474, 27199665, 29903128, 
      10317267, 6828376, 26530628, 28531880, 
      31278401, 2656404, 13492860, 15415872, 
      20530258, 19823384, 33268081, 32508818, 
      9959692, 16530367, 14650382, 20920450, 
      3045328, 5030226, 9124931, 6220013, 
      30765765, 7868179, 2346175, 30352172, 
      14105487, 26274757, 2081623, 20545770, 
      447397, 14394807, 21275550, 479439, 
      25568011, 5553526, 17586366, 3485723, 
      20721028, 18638205, 11152483, 7195535, 
      27701053, 18448570, 12466151, 11030354, 
      28847194, 19706746, 32202122, 13845724, 
      29057843, 19164407, 1105213, 3322427, 
      15710186, 21683552, 8767927, 4404784, 
      32988789, 3417563, 295845, 29723432, 
      1667451, 7523293, 935304, 33444770, 
      4985776, 23360195, 15569550, 14447604]

S2 = [5073760, 14791546, 32875959, 20293792, 
      15818631, 23324437, 21868623, 31870077, 
      22614515, 24544127, 30982356, 8101602, 
      22102646, 31335333, 19060435, 31744710, 
      23595792, 14931663, 555458, 8563305, 
      2698518, 7074034, 32994213, 8354491, 
      140730, 21383307, 2307646, 15675612, 
      30314160, 31336479, 22123520, 15614570, 
      17995191, 23210130, 15384238, 24708128, 
      7799828, 33313597, 5482251, 8217104, 
      12406603, 23793927, 25464079, 10295073, 
      23114311, 9682309, 8331458, 17914031, 
      22925580, 20804435, 827320, 25627651, 
      32995063, 28772690, 10277814, 12396053, 
      14132050, 33200383, 18037349, 15418306, 
      16228604, 5309976, 88761, 3994682, 
      18785693, 3934138, 30939856, 6906569, 
      14155584, 7961013, 15342455, 8715406, 
      669080, 25790209, 13363702, 28131596, 
      713390, 24029217, 15563766, 12977014, 
      31050303, 25712401, 14101769, 27844816, 
      14503017, 23746893, 15206652, 27299893, 
      6792137, 23076644, 20826997, 9806349, 
      23777862, 28614582, 28708713, 26315550, 
      5040184, 12616590, 2569481, 12822804]

S1p = [18170831, 11338665, 13986594, 13958166, 
       27961194, 8900507, 24487120, 24539544, 
       13847326, 20121038, 17110226, 1116247, 
       25308433, 2043221, 18767119, 31675561, 
       33347917, 3525560, 23177813, 6468140, 
       1554101, 8748920, 9250776, 14962679, 
       15616434, 18967513, 27463954, 29632605, 
       17600013, 16176474, 27199665, 29903128, 
       10317267, 6828376, 26530628, 28531880, 
       31278401, 2656404, 13492860, 15415872, 
       20530258, 19823384, 33268081, 32508818, 
       9959692, 16530367, 14650382, 20920450, 
       3045328, 5030226, 13451684, 13348745, 
       6785007, 27278279, 27936976, 10389108, 
       16863122, 27975835, 30054381, 22646401, 
       28817193, 5622925, 1133536, 30865903, 
       10145262, 4589010, 26510018, 5007992, 
       19640434, 963782, 29806492, 5072538, 
       25993054, 1064199, 30597607, 11478229, 
       14528861, 15187996, 10439203, 30017090, 
       23324093, 7840124, 18155557, 2719327, 
       1134296, 26180254, 11206537, 4497198, 
       17492175, 20083939, 14325870, 13489275, 
       14346467, 22256958, 18562002, 10800426, 
       14126137, 229510, 21321641, 22427479]

S2p = [24247740, 281504, 22707929, 10706792, 
       479427, 27391651, 25703426, 22718828, 
       21707634, 15915803, 27931935, 27146128, 
       17018602, 32352142, 22895262, 19281521, 
       25409563, 11881230, 17841258, 16697809, 
       25707550, 10124475, 21809258, 26657158, 
       8275252, 8920048, 30421253, 17593038, 
       2200537, 5943524, 16022612, 197400, 
       14160329, 24117024, 6755791, 16573564, 
       20263143, 10943539, 15650463, 11267571, 
       29663536, 22835209, 28514548, 2160481, 
       15444552, 33069272, 3537856, 26983015, 
       21908754, 16010827, 18460026, 6911068, 
       3104012, 18186083, 17295471, 12759102, 
       10666310, 32908014, 2034658, 25239183, 
       13965411, 5193831, 4998117, 13862971, 
       19923453, 10462582, 6373521, 10126531, 
       17311554, 23089069, 13155273, 22707321, 
       25832874, 15919996, 6454756, 14555684, 
       20317152, 25616120, 7841816, 26275185, 
       28769659, 1832946, 5893352, 26561434, 
       31638965, 26253460, 15499759, 11565590, 
       4146242, 20354251, 33485282, 28166402, 
       10546521, 3172621, 2092850, 17468146, 
       21725694, 2487267, 11501461, 17391658]


def finding_D(P):
    random.seed(P)
    D = random.randint(1,(P-1)//(10**6))
    return D
    
def finding_Dp(P):
    random.seed(P+1)
    Dp = random.randint(1,(P-1)//(10**6))
    return Dp

def random_primes_index(s,count) :
    random.seed(s)
    return(randrange(len(list_of_primes)))

def random_primes_index2(s,count) :
    random.seed(s-1)
    return(randrange(len(list_of_primes)))

def random_primes_index3(s,count) :
    random.seed(s+1)
    return(randrange(len(list_of_primes)))

def random_primes_index4(s,count) :
    random.seed(s+2)
    return(randrange(len(list_of_primes)))

def random_primes_index5(s,count) :
    random.seed(s+3)
    return(randrange(len(list_of_primes)))

def random_primes_index6(s,count) :
    random.seed(s+4)
    return(randrange(len(list_of_primes)))

def random_primes_index7(s,count) :
    random.seed(s+5)
    return(randrange(len(list_of_primes)))

def random_primes_index8(s,count) :
    random.seed(s+6)
    return(randrange(len(list_of_primes)))

def random_primes_index9(s,count) :
    random.seed(s+7)
    return(randrange(len(list_of_primes)))

def random_primes_index10(s,count) :
    random.seed(s+8)
    return(randrange(len(list_of_primes)))


def generate_input(s) :
    N = 1000000000000
    
    p1 = list_of_primes[random_primes_index(s,1)]
    g1 = primitive_roots[random_primes_index(s,1)]
    A1 = values_of_A[random_primes_index(s,1)]
    D1 = finding_D(p1)
    Dp1 = finding_Dp(p1)
    S1_1 = S1[random_primes_index(s,1)]
    S2_1 = S2[random_primes_index(s,1)]
    S1p_1 = S1p[random_primes_index(s,1)]
    S2p_1 = S2p[random_primes_index(s,1)]
    
    p2 = list_of_primes[random_primes_index2(s,1)]
    g2 = primitive_roots[random_primes_index2(s,1)]
    A2 = values_of_A[random_primes_index2(s,1)]
    D2 = finding_D(p2)
    Dp2 = finding_Dp(p2)
    S1_2 = S1[random_primes_index2(s,1)]
    S2_2 = S2[random_primes_index2(s,1)]
    S1p_2 = S1p[random_primes_index2(s,1)]
    S2p_2 = S2p[random_primes_index2(s,1)]
    
    
    p3 = list_of_primes[random_primes_index3(s,1)]
    g3 = primitive_roots[random_primes_index3(s,1)]
    A3 = values_of_A[random_primes_index3(s,1)]
    D3 = finding_D(p3)
    Dp3 = finding_Dp(p3)
    S1_3 = S1[random_primes_index3(s,1)]
    S2_3 = S2[random_primes_index3(s,1)]
    S1p_3 = S1p[random_primes_index3(s,1)]
    S2p_3 = S2p[random_primes_index3(s,1)]
    
    
    p4 = list_of_primes[random_primes_index4(s,1)]
    g4 = primitive_roots[random_primes_index4(s,1)]
    A4 = values_of_A[random_primes_index4(s,1)]
    D4 = finding_D(p4)
    Dp4 = finding_Dp(p4)
    S1_4 = S1[random_primes_index4(s,1)]
    S2_4 = S2[random_primes_index4(s,1)]
    S1p_4 = S1p[random_primes_index4(s,1)]
    S2p_4 = S2p[random_primes_index4(s,1)]
    
    p5 = list_of_primes[random_primes_index5(s,1)]
    g5 = primitive_roots[random_primes_index5(s,1)]
    A5 = values_of_A[random_primes_index5(s,1)]
    D5 = finding_D(p5)
    Dp5 = finding_Dp(p5)
    S1_5 = S1[random_primes_index5(s,1)]
    S2_5 = S2[random_primes_index5(s,1)]
    S1p_5 = S1p[random_primes_index5(s,1)]
    S2p_5 = S2p[random_primes_index5(s,1)]
    
    p6 = list_of_primes[random_primes_index6(s,1)]
    g6 = primitive_roots[random_primes_index6(s,1)]
    A6 = values_of_A[random_primes_index6(s,1)]
    D6 = finding_D(p6)
    Dp6 = finding_Dp(p6)
    S1_6 = S1[random_primes_index6(s,1)]
    S2_6 = S2[random_primes_index6(s,1)]
    S1p_6 = S1p[random_primes_index6(s,1)]
    S2p_6 = S2p[random_primes_index6(s,1)]
    
    p7 = list_of_primes[random_primes_index7(s,1)]
    g7 = primitive_roots[random_primes_index7(s,1)]
    A7 = values_of_A[random_primes_index7(s,1)]
    D7 = finding_D(p7)
    Dp7 = finding_Dp(p7)
    S1_7 = S1[random_primes_index7(s,1)]
    S2_7 = S2[random_primes_index7(s,1)]
    S1p_7 = S1p[random_primes_index7(s,1)]
    S2p_7 = S2p[random_primes_index7(s,1)]
    
    p8 = list_of_primes[random_primes_index8(s,1)]
    g8 = primitive_roots[random_primes_index8(s,1)]
    A8 = values_of_A[random_primes_index8(s,1)]
    D8 = finding_D(p8)
    Dp8 = finding_Dp(p8)
    S1_8 = S1[random_primes_index8(s,1)]
    S2_8 = S2[random_primes_index8(s,1)]
    S1p_8 = S1p[random_primes_index8(s,1)]
    S2p_8 = S2p[random_primes_index8(s,1)]
    
    p9 = list_of_primes[random_primes_index9(s,1)]
    g9 = primitive_roots[random_primes_index9(s,1)]
    A9 = values_of_A[random_primes_index9(s,1)]
    D9 = finding_D(p9)
    Dp9 = finding_Dp(p9)
    S1_9 = S1[random_primes_index9(s,1)]
    S2_9 = S2[random_primes_index9(s,1)]
    S1p_9 = S1p[random_primes_index9(s,1)]
    S2p_9 = S2p[random_primes_index9(s,1)]
    
    p10 = list_of_primes[random_primes_index10(s,1)]
    g10 = primitive_roots[random_primes_index10(s,1)]
    A10 = values_of_A[random_primes_index10(s,1)]
    D10 = finding_D(p10)
    Dp10 = finding_Dp(p10)
    S1_10 = S1[random_primes_index10(s,1)]
    S2_10 = S2[random_primes_index10(s,1)]
    S1p_10 = S1p[random_primes_index10(s,1)]
    S2p_10 = S2p[random_primes_index10(s,1)]
    

    return (p1,g1,A1,D1,Dp1,S1_1,S2_1,S1p_1,S2p_1), (p2,g2,A2,D2,Dp2,S1_2,S2_2,S1p_2,S2p_2), (p3,g3,A3,D3,Dp3,S1_3,S2_3,S1p_3,S2p_3), (p4, g4, A4,D4,Dp4,S1_4,S2_4,S1p_4,S2p_4), (p5, g5, A5,D5,Dp5,S1_5,S2_5,S1p_5,S2p_5), (p6, g6, A6,D6,Dp6,S1_6,S2_6,S1p_6,S2p_6), (p7, g7, A7,D7,Dp7,S1_7,S2_7,S1p_7,S2p_7), (p8, g8, A8,D8,Dp8,S1_8,S2_8,S1p_8,S2p_8), (p9, g9, A9,D9,Dp9,S1_9,S2_9,S1p_9,S2p_9), (p10, g10, A10,D10,Dp10,S1_10,S2_10,S1p_10,S2p_10)

