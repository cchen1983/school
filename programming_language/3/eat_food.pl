food(apple).
food(oyster).
food(X) :- eat(_, X), !.
eat(tom, snake).
eat(sue, X) :- eat(tom, X).
eat(john, X) :- food(X).

/* Queries
eat(john,X).
eat(sue, X).
eat(sue, X), eat(john, X).
eat(X, snake).
*/
