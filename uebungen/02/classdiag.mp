input metauml;

def Label(expr ltext)(suffix adir)(expr cpoint) =
   item(iAssoc)(ltext)(obj.adir = cpoint);
enddef;

def Bidirect(expr firstpoint, secondpoint) =
   link(associationUni)(firstpoint -- secondpoint);
   link(associationUni)(secondpoint -- firstpoint);
enddef;

def Unidirect(expr firstpoint, secondpoint) =
   link(associationUni)(firstpoint -- secondpoint);
enddef;

def Uni(expr firstpoint, secondpoint)
      (expr firstdegree)(suffix firstdir)
      (expr seconddegree)(suffix seconddir)
      (expr description)(suffix ddir) =
   Unidirect(firstpoint, secondpoint);
   Label(firstdegree, firstdir, firstpoint);
   Label(seconddegree, seconddir, secondpoint);
   Label(description, ddir, 0.5[firstpoint, secondpoint]);
enddef;

def Bi(expr firstpoint, secondpoint)
      (expr firstdegree)(suffix firstdir)
      (expr seconddegree)(suffix seconddir)
      (expr description)(suffix ddir) =
   Bidirect(firstpoint, secondpoint);
   Label(firstdegree, firstdir, firstpoint);
   Label(seconddegree, seconddir, secondpoint);
   Label(description, ddir, 0.5[firstpoint, secondpoint]);
enddef;

beginfig(1);

   % classes
   Class.GameDB("GameDB")
      ()
      (
	 "+getPlayerByName(playerName)",
	 "+getRecentGames()",
	 "+addPlayer(name)",
	 "+addGame(firstPlayer, secondPlayer)",
      );
   Class.Game("Game")
      ()
      (
	 "+getFirstPlayer()",
	 "+getSecondPlayer()",
	 "+getMoves()",
      );
   Class.Player("Player")
      ()
      (
	 "+getName()",
	 "+getGames()",
	 "+getNumberOfGames()",
	 "+getLastGame()",
      );
   Class.Move("Move")
      ()
      (
	 "+getComments()",
	 "+toString()",
      );
   Class.Comment("Comment")
      ()
      (
	 "+getAuthor()",
	 "+getText()",
      );
   % arrangement
   dx = 1.2 (xpart GameDB.e - xpart GameDB.w);
   dy = 0.5 dx;

   0.5[Game.c, Player.c] = GameDB.s - (0, dy);
   Game.e = Player.w - (dx, 0);
   Move.n = Game.s - (0, dy);
   xpart Comment.n = xpart Player.s;
   ypart Comment.n = ypart Move.n;

   % draw classes
   drawObjects(GameDB, Game, Player, Move, Comment);

   % relations between the classes
   Uni(GameDB.sw, Game.n)("1", n)("*", s)("hosts", e);
   Uni(GameDB.se, Player.n)("1", n)("*", s)("hosts", w);
   Uni(Game.s, Move.n)("1", nw)("*", sw)("includes", e);
   Bi(1/3 [Game.ne, Game.se], 1/3[Player.nw, Player.sw])("*", nw)("1", ne)
      ("first player", s);
   Bi(2/3 [Game.ne, Game.se], 2/3[Player.nw, Player.sw])("*", nw)("1", ne)
      ("second player", n);
   Uni(Move.e, Comment.w)("1", nw)("*", ne)("carries", s);
   Uni(Comment.n, Player.s)("*", sw)("1", nw)("author", w);
endfig;
end.
