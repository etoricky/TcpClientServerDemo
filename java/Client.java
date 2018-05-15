import java.io.*;
import java.net.*;

class Client {
    public static void main(String argv[]) throws Exception {
        BufferedReader inFromUser = new BufferedReader(new InputStreamReader(System.in));
        Socket clientSocket = new Socket("localhost", 6789);
        DataOutputStream outToServer = new DataOutputStream(clientSocket.getOutputStream());
        BufferedReader inFromServer = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
        while (true) {
            String sentence = inFromUser.readLine();
            if (sentence=="quit") {
                break;
            }
            outToServer.writeBytes(sentence + '\n');
            String modifiedSentence = inFromServer.readLine();
            System.out.println("FROM SERVER: " + modifiedSentence);
        }
        clientSocket.close();
    }
}