import java.net.*;
import java.io.*;
import java.util.Random;

public class JokeServer
{
  // I am lazy, Just add some jokes here :)
  private static String[] jokes = {
    "test\n1",
    "test\n2",
    "test\n3",
    "test\n4",
    "test\n5",
    "test\n6",
    "test\n7",
    "test\n8",
    "test\n9",
    "test\n10"
  };
  public static void main(String[] args)
  {
    Random rand = new Random();
    try
    {
      ServerSocket sock = new ServerSocket(6033);

      while(true)
      {
        Socket client = sock.accept();

        PrintWriter pout = new PrintWriter(client.getOutputStream(), true);

        // Random selection of joke
        int index = rand.nextInt(jokes.length) + 1;
        String send = jokes[index];
        pout.println(send);

        client.close();
      }
    }
    catch (IOException exception)
    {
      System.err.println(exception);
    }
  }
}
