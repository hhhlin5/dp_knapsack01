Problem (Knapsack Variant). 

Consider integers 𝑊 ≥ 0 and l ≥ 0 and items 1, ... , 𝑛, where each item 𝑖 has weight 𝑤𝑖 > 0 and value 𝑣𝑖 > 0. The value (resp. weight) of a subset of items is the sum of the values (resp. weights) of the items in the subset. If there exists a subset of exactly l items whose total weight is exactly 𝑊, then find such a subset whose value is maximum. Otherwise, report that no such subset exists. Define 𝑂𝑃𝑇(𝑖, 𝑤, 𝑘) to be the maximum value of any subset of the first 𝑖 items of size exactly 𝑘 whose total weight is exactly 𝑤. Consider the following recursive equation.

Consider the following recursive equation: 
When i < k, OPT(i,w,k) = −∞ 
When w > 0 and k = 0, OPT(i,w,k) = −∞ 
When w = 0 and k > 0, OPT(i,w,k) = −∞ 
When w = 0 and k = 0, OPT(i,w,k) = 0 
When wi > w, OPT(i,w,k) = OPT(i-1,w,k) 
Otherwise, OPT(i,w,k) = max{OPT(i-1,w,k), vi + OPT(i-1,w-wi,k-1)}

Program a bottom-up dynamic programming algorithm to solve this problem using the above recursive equation. You will need a three-dimensional matrix to store solutions to subproblems. You will also need a traceback function that traverses the matrix to find a solution to the problem if one exists. If no solution exists, your program should say so.
