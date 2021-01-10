import java.util.Scanner;

public class Lab4Plate{

     public static void main(String []args){
        String command="", output="";
		Scanner in = new Scanner(System.in);
		int[] stack = new int[1000];
		int num, n_stack=0;
		
		do{
			if (in.hasNext()){
				command = in.next();
				if (command.equals("push")){
					if(in.hasNextInt()){
						num = in.nextInt();
						stack[n_stack++] = num;
						output = output + addOutput(stack, n_stack);
					}
				}else if (command.equals("pop")){
					--n_stack;
					output = output + addOutput(stack, n_stack);
				}
			}
				
		}while(!command.equals("end!"));
		
		in.close();
		System.out.println(output);
		
     }

	 public static String addOutput(int stack[], int n_stack){
		 String temp = "|";
		 for (int i=n_stack-1; i>=0; i--){
			 temp+=" "+stack[i];
		 }
		 temp+=" |\n";
		 return temp;
	 }

}