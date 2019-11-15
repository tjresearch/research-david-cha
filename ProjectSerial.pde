import processing.serial.*;
import java.io.*;
int mySwitch=0;
int counter=0;
String [] subtext;   
String [][] data;
Serial myPort;

//https://www.youtube.com/watch?v=7iMMUO0J3h4
void setup(){
 //Create a switch that will control the frequency of text file reads.
 //When mySwitch=1, the program is setup to read the text file.
 //This is turned off when mySwitch = 0
 mySwitch=1;
 
 //Open the serial port for communication with the Arduino
 //Make sure the COM port is correct
 //myPort = new Serial(this, "COM9", 9600);
 //myPort.bufferUntil('\n');
}

void draw() {
 readData("C:/Users/David Cha/PycharmProjects/Senior Project/data.txt");
 
 for(int i=0; i<data.length; i++){
 //myPort.write(Integer.parseInt(data[i][2].substring(5)));
 System.out.println(""+(Integer.parseInt(data[i][2].substring(5))));
 delay(Integer.parseInt(data[i][4].substring(5)));
 System.out.println("velocity "+(Integer.parseInt(data[i][3].substring(9))));
 //myPort.write(0);
 delay(100);
 }
} 


void readData(String myFileName){
 
 File file=new File(myFileName);
 BufferedReader br=null;
 
 try{
 br=new BufferedReader(new FileReader(file));
 String text=null; 
 int count=0;
 while((text=br.readLine())!=null)
   count+=1;
 data = new String[count][5];
 count=0;
 br=new BufferedReader(new FileReader(file));
 while((text=br.readLine())!=null){
 subtext = splitTokens(text," ");
 for(int i=0; i<5; i++)
   data[count][i]=subtext[i];
 count+=1;
 }
 }catch(FileNotFoundException e){
 e.printStackTrace();
 }catch(IOException e){
 e.printStackTrace();
 }finally{
 try {
 if (br != null){
 br.close();
 }
 } catch (IOException e) {
 e.printStackTrace();
 }
 }
}
