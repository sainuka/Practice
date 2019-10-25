%This assignment uses facts and rules to explain the Bernoulli family tree

%Facts
parent(johann, nicolausII).
parent(johann, daniel).
parent(johann, johannII).
parent(johannII, jacobII).
parent(johannII, johannIII).
parent(dorothea, nicolausII).
parent(dorothea, daniel).
parent(dorothea, johannII).

male(johann).
male(nicolausII).
male(johannII).
male(jacobII).
male(johannIII).

female(dorothea).

%Rules
father(X, Y) :- parent(X, Y), male(X).
mother(X, Y) :- parent(X, Y), female(X).

grandfather(X, Y) :- parent(Z, Y), parent(X, Z), male(X).
grandmother(X, Y) :- parent(Z, Y), parent(X, Z), female(X).

son(X, Y) :- parent(Y, X), male(X).
daughter(X, Y) :- parent(Y, X), female(X).

brother(X, Y) :- parent(Z, X), parent(Z, Y), male(X), X #\= Y.
sister(X, Y) :- parent(Z, X), parent(Z, Y), female(X), X #\= Y.

aunt(X, Y) :- parent(Z, Y), sister(Z, X).
uncle(X, Y) :- parent(Z, Y), brother(Z, X).

niece(X, Y) :- aunt(Y, X), female(X).
niece(X, Y) :- uncle(Y, X), female(X).

nephew(X, Y) :- aunt(Y, X), male(X).
nephew(X, Y) :- uncle(Y, X), male(X).
