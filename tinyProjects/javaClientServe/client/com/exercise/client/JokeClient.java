import java.net.*;
import java.io.*;

public class JokeClient
{
  public static void main(String[] args)
  {
    try
    {
      Socket sock = new Socket("127.0.0.1", 6033);

      InputStream in = sock.getInputStream();
      BufferedReader bin = new BufferedReader(new InputStreamReader(in));

      String line;
      while ( (line = bin.readLine()) != null)
      {
        System.out.println(line);
      }
      sock.close();
    }
    catch (IOException exception)
    {
      System.err.println(exception);
    }
  }
}
