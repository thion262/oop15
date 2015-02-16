input metauml;

beginfig(1);

   % classes
   Class.Employee("Employee")
      (
	 "id",
	 "name"
      )
      (
	 "+Employee()",
      );
   Class.Department("Department")
      (
	 "name"
      )
      (
	 "+Department()",
	 "+getEmplyees()",
	 "+getHead()",
	 "+setHead()",
	 "+addEmployee()",
	 "+remEmployee()",
      );
   % arrangement
   distance = 1.2 (xpart Employee.e - xpart Employee.w);

   Department.nw = Employee.ne + (distance, 0);

   % draw classes
   drawObjects(Employee, Department);

   % relations between the classes
   pair memberOf.w, memberOf.e, memberOf.c;
   memberOf.w = 0.5[Employee.ne, Employee.e];
   memberOf.e = memberOf.w + (distance, 0);
   memberOf.c = 0.5[memberOf.w, memberOf.e];
   link(associationUni)(memberOf.e -- memberOf.w);
   item(iAssoc)("1..*")(obj.ne = memberOf.e);
   item(iAssoc)("*")(obj.nw = memberOf.w);
   item(iAssoc)("memberOf")(obj.s = memberOf.c);

   pair headOf.w, headOf.e, headOf.c;
   headOf.w = 0.5[Employee.se, Employee.e];
   headOf.e = headOf.w + (distance, 0);
   headOf.c = 0.5[headOf.w, headOf.e];
   link(associationUni)(headOf.e -- headOf.w);
   item(iAssoc)("*")(obj.ne = headOf.e);
   item(iAssoc)("0..1")(obj.nw = headOf.w);
   item(iAssoc)("headOf")(obj.s = headOf.c);
endfig;
end.
