sublistfw([], _).
sublistfw([X|Xr], [X|Yr]) :- sublistfw(Xr, Yr).
sublistbw(X, [_|Yr], I) :- sublistfw(X, Yr), print(I); J is I+1, sublistbw(X,Yr,J).
sublist(X, Y) :- sublistfw(X, Y), print(1); I is 2, sublistbw(X, Y, I).
