\ENCODING=ISO-8859-1
\Problem name: IloCplex

Maximize
 obj1: 10000 x(Faz1)(Soja)#0 + 4000 x(Faz1)(Arroz)#1 + 10000 x(Faz2)(Soja)#2
       + 4000 x(Faz2)(Arroz)#3 + 10000 x(Faz3)(Soja)#4 + 4000 x(Faz3)(Arroz)#5
       + 10000 x(Faz4)(Soja)#6 + 4000 x(Faz4)(Arroz)#7
Subject To
 __AreaFaz(Faz1)._#0:     x(Faz1)(Soja)#0 + x(Faz1)(Arroz)#1 <= 400
 __AreaFaz(Faz2)._#1:     x(Faz2)(Soja)#2 + x(Faz2)(Arroz)#3 <= 650
 __AreaFaz(Faz3)._#2:     x(Faz3)(Soja)#4 + x(Faz3)(Arroz)#5 <= 350
 __AreaFaz(Faz4)._#3:     x(Faz4)(Soja)#6 + x(Faz4)(Arroz)#7 <= 700
 ConsAgua(Faz1).#4:       7 x(Faz1)(Soja)#0 + 4 x(Faz1)(Arroz)#1 <= 1800
 ConsAgua(Faz2).#5:       7 x(Faz2)(Soja)#2 + 4 x(Faz2)(Arroz)#3 <= 2200
 ConsAgua(Faz3).#6:       7 x(Faz3)(Soja)#4 + 4 x(Faz3)(Arroz)#5 <= 950
 ConsAgua(Faz4).#7:       7 x(Faz4)(Soja)#6 + 4 x(Faz4)(Arroz)#7 <= 650
 AreaMaxCult(Soja).#8:    x(Faz1)(Soja)#0 + x(Faz2)(Soja)#2 + x(Faz3)(Soja)#4
                          + x(Faz4)(Soja)#6 <= 800
 AreaMaxCult(Arroz).#9:   x(Faz1)(Arroz)#1 + x(Faz2)(Arroz)#3
                          + x(Faz3)(Arroz)#5 + x(Faz4)(Arroz)#7 <= 880
 Proporc(Faz1)(Faz2).#10: 0.0025 x(Faz1)(Soja)#0 + 0.0025 x(Faz1)(Arroz)#1
                          - 0.00153846153846154 x(Faz2)(Soja)#2
                          - 0.00153846153846154 x(Faz2)(Arroz)#3  = 0
 Proporc(Faz1)(Faz3).#11: 0.0025 x(Faz1)(Soja)#0 + 0.0025 x(Faz1)(Arroz)#1
                          - 0.00285714285714286 x(Faz3)(Soja)#4
                          - 0.00285714285714286 x(Faz3)(Arroz)#5  = 0
 Proporc(Faz1)(Faz4).#12: 0.0025 x(Faz1)(Soja)#0 + 0.0025 x(Faz1)(Arroz)#1
                          - 0.00142857142857143 x(Faz4)(Soja)#6
                          - 0.00142857142857143 x(Faz4)(Arroz)#7  = 0
 Proporc(Faz2)(Faz1).#13: - 0.0025 x(Faz1)(Soja)#0 - 0.0025 x(Faz1)(Arroz)#1
                          + 0.00153846153846154 x(Faz2)(Soja)#2
                          + 0.00153846153846154 x(Faz2)(Arroz)#3  = 0
 Proporc(Faz2)(Faz3).#14: 0.00153846153846154 x(Faz2)(Soja)#2
                          + 0.00153846153846154 x(Faz2)(Arroz)#3
                          - 0.00285714285714286 x(Faz3)(Soja)#4
                          - 0.00285714285714286 x(Faz3)(Arroz)#5  = 0
 Proporc(Faz2)(Faz4).#15: 0.00153846153846154 x(Faz2)(Soja)#2
                          + 0.00153846153846154 x(Faz2)(Arroz)#3
                          - 0.00142857142857143 x(Faz4)(Soja)#6
                          - 0.00142857142857143 x(Faz4)(Arroz)#7  = 0
 Proporc(Faz3)(Faz1).#16: - 0.0025 x(Faz1)(Soja)#0 - 0.0025 x(Faz1)(Arroz)#1
                          + 0.00285714285714286 x(Faz3)(Soja)#4
                          + 0.00285714285714286 x(Faz3)(Arroz)#5  = 0
 Proporc(Faz3)(Faz2).#17: - 0.00153846153846154 x(Faz2)(Soja)#2
                          - 0.00153846153846154 x(Faz2)(Arroz)#3
                          + 0.00285714285714286 x(Faz3)(Soja)#4
                          + 0.00285714285714286 x(Faz3)(Arroz)#5  = 0
 Proporc(Faz3)(Faz4).#18: 0.00285714285714286 x(Faz3)(Soja)#4
                          + 0.00285714285714286 x(Faz3)(Arroz)#5
                          - 0.00142857142857143 x(Faz4)(Soja)#6
                          - 0.00142857142857143 x(Faz4)(Arroz)#7  = 0
 Proporc(Faz4)(Faz1).#19: - 0.0025 x(Faz1)(Soja)#0 - 0.0025 x(Faz1)(Arroz)#1
                          + 0.00142857142857143 x(Faz4)(Soja)#6
                          + 0.00142857142857143 x(Faz4)(Arroz)#7  = 0
 Proporc(Faz4)(Faz2).#20: - 0.00153846153846154 x(Faz2)(Soja)#2
                          - 0.00153846153846154 x(Faz2)(Arroz)#3
                          + 0.00142857142857143 x(Faz4)(Soja)#6
                          + 0.00142857142857143 x(Faz4)(Arroz)#7  = 0
 Proporc(Faz4)(Faz3).#21: - 0.00285714285714286 x(Faz3)(Soja)#4
                          - 0.00285714285714286 x(Faz3)(Arroz)#5
                          + 0.00142857142857143 x(Faz4)(Soja)#6
                          + 0.00142857142857143 x(Faz4)(Arroz)#7  = 0
End
