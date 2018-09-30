
define printNumAndString(num a,string b):void{
  pdf::print(a);
  pdf::print(a + pdf::to_string(b));
}

define emptyTest(num a):void{

}

string s = "testString";

if(s == "testString"){
    printNumAndString();
}else{
    pdf::print("No Match");
}