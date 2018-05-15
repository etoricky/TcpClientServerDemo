import java.io.*;
import java.net.*;

class Server {
    public static void main(String argv[]) throws Exception {
        ServerSocket welcomeSocket = new ServerSocket(6789);

        while (true) {
            Socket connectionSocket = welcomeSocket.accept();
            BufferedReader inFromClient =
                new BufferedReader(new InputStreamReader(connectionSocket.getInputStream()));
            DataOutputStream outToClient = new DataOutputStream(connectionSocket.getOutputStream());
            
            while (true) {
                String clientSentence = inFromClient.readLine();
                System.out.println("Received: " + clientSentence);
                String capitalizedSentence = clientSentence.toUpperCase() + '\n';
                outToClient.writeBytes(capitalizedSentence);
            }
        }
    }
}