#include <iostream>
#include <cctype>
#include <string>
#include<cstdlib>
#include <sstream>
#include <unordered_map>
#include<vector>
bool run=true;

std::unordered_map<std::string, double> vars;
std::unordered_map<std::string,std::string> strVars;
bool cie(std::string token){
  return ((vars.count(token) || strVars.count(token))?true:false);
    
}
//checks if the data is exist
std::string checkVal(std::string token)
{
  double val=0;
  std::string retStr;
  if (vars.count(token) || strVars.count(token))
  {
     if(vars.count(token))
     {
		    val=vars[token];
		    retStr=std::to_string(val);
	   }
	   else
	      retStr=strVars[token];
	
  } 
  else
    {
     std::cout << "ERROR: the value of " << token << " is not initialize yet." << "\n";
     return 0;
    }
	
  return retStr;
}


//for operation
double operation(std::string op,double val,double result)
{
	    if(op=="+") result+=val;
      else if(op=="-") result-=val;
      else if(op=="*") result=result*=val;
      else if(op=="/") result=result/val;
      else result=val;
  return result;
}

//for ADD Parameter
double addOpt(std::string expr)
{
  while (!expr.empty() && std::isspace(expr.front()))
		expr.erase(expr.begin());
  double sum;
  double val=0;
  std::string op="+";
  std::stringstream data(expr);
  std::string token;
  	while (data >> token)
	{
    if (std::isalpha(token[0])!=0)
    {
      std::string checksrt=checkVal(token);
      if(std::isalpha(checksrt[0])==0)
      val=std::stod(checkVal(token));
      else
      {
        std::cout<<"ERROR: string cannot be added...\n";
        return 0;  
      }
    }
      
		else
      val=std::stod(token);
      sum=operation(op,val,sum); 
    }
  return sum;
}


  //need to work            
double expVal(std::string expr)
{
	std::stringstream data(expr);
	double val = 0,result = 0;
	std::string token;
  std::string op = "+";
	while (data >> token)
	{
    if (std::isalpha(token[0])!=0)
    {
      val=std::stod(checkVal(token));
		}
		else
      val=std::stod(token);
      result=operation(op,val,result);//need to work on that
			data >> op;
		
	}
  
	return result;
}

void expLine(std::string line)
{

	if (line.rfind("print", 0) == 0) // working nice
	{

		std::string exp = line.substr(6);

		if (exp.find('[') != std::string::npos)
		{
			while (!exp.empty() && std::isspace(exp.front()))
				exp.erase(exp.begin());
			if (exp.find(']') != std::string::npos)
			{
				while (!exp.empty() && isspace(exp.back()))
					exp.pop_back();
				exp.pop_back();
				exp.erase(exp.begin());
				std::cout << exp << "\n";
			}
      
			
      
      else
				std::cout << "ERROR Syntex . missign [ or ]\n";
		}

		else if(cie(exp))
		{
      std::string val;    
			 val=(checkVal(exp));       
			std::cout << val << "\n";
		}
    else
    {
      std::string val;    
			 val=std::to_string(expVal(exp));       
			std::cout << val << "\n";
    }
	}

	else if (line.rfind("add", 0) == 0) //working nice
  {
     std::string exp = line.substr(4);
     double val=addOpt(exp);
     std::cout << val<<"\n";///////////////////
  }
  	else if(line.find('=')!=std::string::npos && line.find('[')==std::string::npos)
	{
     
        double val = 0;
        std::string var = line.substr(0, line.find("="));
        std::string value = line.substr(line.find("=")+1);
        while (!var.empty() && std::isspace(var.back()))
          var.pop_back();
        while (!value.empty() && std::isspace(value.front()))
          value.erase(value.begin());
        val = expVal(value);

        vars[var] = val;
        
      
		
	}
  
	else if(line.find('[')!=std::string::npos && line.find('=')!= std::string::npos )
	{
		std::string var = line.substr(0, line.find("="));
        std::string value = line.substr(line.find("=")+1);
        while (!var.empty() && std::isspace(var.back()))
          var.pop_back();
        while (!value.empty() && std::isspace(value.front()))
          value.erase(value.begin());
        value.erase(value.begin());
        value.pop_back();
    if(vars.count(var))
      vars.erase(var);
        strVars[var] = value;
	}
  else if(line.rfind("exit",0)==0)
    run=false;
  else if(line.rfind("clear",0)==0)
    system("clear");
    
	else
		std::cout << "error command not found:" << line << "\n";
}

void sepLine(std::string line)
{
  
  if(line.find(',')!=std::string::npos)
  {
    std::vector<std::string> vec;
    std::string temp_s = line; // Create a mutable copy of the string
    size_t pos = 0;
    std::string token;
 std::string delimiter = ",";
    while ((pos = temp_s.find(delimiter)) != std::string::npos) {
        token = temp_s.substr(0, pos);
        vec.push_back(token);
        temp_s.erase(0, pos + 1); 
    }
    vec.push_back(temp_s);
    
     for (const std::string& token : vec) {
        expLine(token);
    }
  }
  else
    expLine(line);
  
}

int main()
{
	std::string line;
	while (run)
	{
		std::cout << "=>";/////////////////
		std::getline(std::cin, line);
		while (!line.empty() && std::isspace(line.front()))
			line.erase(line.begin());
    
		if (line == "exit")
			break;
		else if (line.empty())
			continue;
    else if(line=="clear")
      system("clear");
		else
			sepLine(line);
	}
	return 0;
}
