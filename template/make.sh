
echo ""
echo "      PLEASE CHOOSE"
echo "++++++++++++++++++++++++++++"
echo "	1. Generate(g)"
echo "	2. Append(a)"
echo "	3. Cover(c)"
echo "	4. Clean(l)"
echo "	5. Exit(e)"
echo "++++++++++++++++++++++++++++"
echo ""

read INPUT
case $INPUT in
1|g|G|generate|Generate)
     ./Template.sh
     ;; # same as break;
2|a|A|append|Append)
     ./Template.sh
     ;;
3|c|C|cover|Cover)
     rm -rf docs include src tests tmp
     rm LICENSE COPYING Makefile README.md FAQ INSTALL NOTICE     
     ./Template.sh
     ;;
4|l|L|clean|Clean)
     rm -rf docs include src tests tmp
     rm LICENSE COPYING Makefile README.md FAQ INSTALL NOTICE     
     ;;
5|e|E|exit|Exit)
     echo "USER ABORT."
     ;;
*)
     echo "NOT A VALID INPUT."
     ;;
esac 
