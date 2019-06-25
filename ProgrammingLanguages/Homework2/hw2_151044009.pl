% CSE341 – Programming Languages (Fall 2017)
% Homework #2 - #Prolog
% Şevval MEHDER 151044009

% knowledge base

flight(ankara,istanbul,5). % fact: Ankara and Istanbul has a flight with cost 5.
flight(ankara,trabzon,2).  % fact: Ankara and Trabzon has a flight with cost 2.
flight(ankara,izmir,6).    % fact: Ankara and Izmir has a flight with cost 6.
flight(ankara,konya,8).    % fact: Ankara and Konya has a flight with cost 8.

flight(antalya,izmir,1).      % fact: Antalya and Izmır has a flight with cost 1.
flight(antalya,diyarbakır,5). % fact: Antalya and Diyarbakır has a flight with cost 5.

flight(diyarbakır,konya,1).   % fact: Diyarbakır and Konya has a flight with cost 1.
flight(diyarbakır,antalya,5). % fact: Diyarbakır and Antalya has a flight with cost 5.

flight(edirne,edremit,5). % fact: Edirne and Edremit has a flight with cost 5.

flight(edremit,erzincan,7). % fact: Edremit and Erzincan has a flight with cost 7.
flight(edremit,edirne,5).   % fact: Edremit and Edirne has a flight with cost 5.

flight(erzincan,edremit,7). % fact: Erzincan and Edremit has a flight with cost 7.

flight(gaziantep,kars,3).   % fact: Gaziantep and Kars has a flight with cost 3.

flight(istanbul,izmir,3).   % fact: Istanbul and Izmir has a flight with cost 3.
flight(istanbul,ankara,5).  % fact: Istanbul and Ankara has a flight with cost 5.
flight(istanbul,trabzon,3). % fact: Istanbul and Trabzon has a flight with cost 3.

flight(izmir,ankara,6).   % fact: Izmır and Ankara has a flight with cost 6.
flight(izmir,istanbul,3). % fact: Izmır and Istanbul has a flight with cost 3.
flight(izmir,antalya,1).  % fact: Izmır and Antalya has a flight with cost 1.

flight(kars,gaziantep,3). % fact: Kars and Gaziantep has a flight with cost 3.
flight(kars,konya,5).     % fact: Kars and Konya has a flight with cost 5.

flight(konya,ankara,8).     % fact: Konya and Ankara has a flight with cost 8.
flight(konya,diyarbakır,1). % fact: Konya and Diyarbakır has a flight with cost 1.
flight(konya,kars,5).       % fact: Konya and Kars has a flight with cost 5.

flight(trabzon,istanbul,3). % fact: Trabzon and Istanbul has a flight with cost 3.
flight(trabzon,ankara,2).   % fact: Trabzon and Ankara has a flight with cost 2.

% *******************************************************
%
% PART 1
%
% *******************************************************

% rules

route(X,Y,C) :-	travel(X,Y,C,[]).    %There is a path if we can travel from one to other

travel(X,Y,C,R) :-	flight(X,Y,C), 
					\+ member(Y,R).  % If Y is not in Road(visited)

travel(X,Y,C,R)	:-	flight(X,Z,C1), 
					\+ member(Z,R),   % Is not Z in R(oad) - visited?
					not(Z == Y),     % If it is not a destination 
					travel(Z,Y,C2, [X|R]), 
					C is C1 + C2.

% *******************************************************
%
% PART 2
%
% *******************************************************

croute(X,Y,C) :-	setof(M, route(X,Y,M), Set), % Create a set with costs
					min_member(C, Set).          % Then find the minimum cost

% *******************************************************
%
% PART 3
%
% *******************************************************

when(a, 10). % Time of the A is 10.
when(b, 12). % Time of the B is 12.
when(c, 11). % Time of the C is 11.
when(d, 16). % Time of the D is 16.
when(e, 17). % Time of the E is 17.
% 3.0 - Add one or two more sessions
when(f,14).   % Time of the F is 14.
when(g,13).   % Time of the G is 14.

where(a, 101). % Place of the session A is 101.
where(b, 104). % Place of the session B is 104.
where(c, 102). % Place of the session C is 102.
where(d, 103). % Place of the session D is 103.
where(e, 103). % Place of the session E is 103.
% 3.0 - Add one or two more sessions
where(f,104). % Place of the session F is 104.
where(g,101). % Place of the session G is 101.

attendee(1,a). % Attendee 1 is enrolled in session A.
attendee(1,b). % Attendee 1 is enrolled in session B.
attendee(2,a). % Attendee 2 is enrolled in session A.
attendee(3,b). % Attendee 3 is enrolled in session B.
attendee(4,c). % Attendee 4 is enrolled in session C.
attendee(5,d). % Attendee 5 is enrolled in session D
attendee(6,d). % Attendee 6 is enrolled in session D.
attendee(6,a). % Attendee 6 is enrolled in session A.
% 3.0 - Add at least 5 more attendees each enrolled to two or more sessions.
attendee(7,c).  % Attendee 7 is enrolled in session C.
attendee(7,g).  % Attendee 7 is enrolled in session G.
attendee(8,a).  % Attendee 8 is enrolled in session A.
attendee(8,b).  % Attendee 8 is enrolled in session B.
attendee(8,e).  % Attendee 8 is enrolled in session E.
attendee(9,a).  % Attendee 9 is enrolled in session A.
attendee(9,g).  % Attendee 9 is enrolled in session G.
attendee(10,g). % Attendee 10 is enrolled in session G.
attendee(10,d). % Attendee 10 is enrolled in session D.
attendee(11,a). % Attendee 11 is enrolled in session A.
attendee(11,f). % Attendee 11 is enrolled in session F.
attendee(11,d). % Attendee 11 is enrolled in session D.



% 3.1
schedule(S,P,T) :- 	attendee(S,X), % Attendee C is enrolled the session X
					where(X,P),    % The time of the session X is P.
					when(X,T).     % And the placeof the session X is T.


% 3.2  
usage(P,T) :-	where(X,P),        % There is a X in place P
				when(X,T).         % and the time on T.

% 3.3
conflict(X,Y) :-	( when(X,F),                               % Let time of X is F.
					  when(Y,G),                               % Let time of Y is G.
					  ( (F is G + 1); (F is G); (F is G - 1) ) % If the time of X, 1 hour earlier or later, or same time with Y
					) 
					;                                          % or
					(
					where(X,W),                                % Place of the X is same with the place of the Y.
					where(Y,W)
					).

% 3.4
meet(X,Y) :-	attendee(X,S1),                                     % X is enrolled in session S1.
				attendee(Y,S2),                                     % Y is enrolled in session S2.
				(when(S1,T), when(S2,T), where(S1,P), where(S1,P)). % If S1 and S2 are in same room and the same time

% *******************************************************
%
% PART 4
%
% *******************************************************

% 4.1 Define a Prolog predicate “union(L,S,U)” that finds the union of all the elements of L and S. The
%result will be bound to U

union(L,S,U) :-	unionHelper(L,S,U).

% When the current element is in both list, dont add it
unionHelper([Head|Tail], S, U) :-	member(Head, S),	
									unionHelper(Tail,S,U).

% When the current element is in only one list, add it 
unionHelper([Head|TailL], S, [Head|TailU]) :-	\+ member(Head,S),
												unionHelper(TailL,S,TailU).

% When the first list became a empty list
unionHelper([],S,S). % The result must be the same of other list.

% When given two list is empty
unionHelper([],[],[]). % The result must be empty list.



% 4.2 Define a Prolog predicate “intersect(L1,L2,I)” that finds the intersection of L1 and L2 binding the
%results to I.

intersect(L1,L2,I) :-	intersectHelper(L1,L2,I).

% When the current element is in both list, add it
intersectHelper([Head|Tail], L2, [Head|TailI]) :-	member(Head,L2),
													intersectHelper(Tail, L2, TailI).

% When the current element is in only one list, dont add it
intersectHelper([Head|Tail], L2, I) :-	\+ member(Head, L2),
										intersectHelper(Tail,L2,I).

% If the first list become empty
intersectHelper([], _, []).



% 4.3 Define a Prolog predicate “flatten(L,F)” that flattens the list of lists (that elements of L can be list
% of lists, e.g. nested lists are possible) in L binding results to F.



flatten(L,F) :-	flattenHelper(L,F,[]).  % Call the helper

% If the scanning list is done, cut the all call.
flattenHelper([],F,F) :- !. 

flattenHelper([LHead|LTail], F, List) :-	% Take the first element and recursion function Call
									% If the first element is list make recursive call again
									% Otherwise add to list of F.
									!,
									addItem(LHead,F,Added), 
									% Go on with other part of list.
									% The list of added is return list with added element.
								 	flattenHelper(LTail,Added,List).

% Add an element and use the new list(F) with added element
addItem(ToAdd, [ToAdd|F], F).




