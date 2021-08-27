import java.io.*;
import java.net.*;
import java.lang.*;

import com.dalsemi.system.BytePort;

// The client
class CLIENT
    extends Thread
{
    String stream_name;
    String server_name;
    int    port;
    byte[] buffer;

    //
    // Constructor
    //
    CLIENT (String server_name, int port, String stream_name)
    {
        // Initialize members
        this.stream_name = stream_name;
        this.server_name = server_name;
        this.port        = port;
    }

    //
    // Run the client
    //
    public void run ()
    {
        // Socket to connect to server
        Socket sd = null;

        try
            {
                // Connect to server
                sd = new Socket (server_name, port);

                // Diagnostics
                System.out.println ("Connected to " + server_name +
                                    ":" + port);
                // Output stream
                OutputStream out = sd.getOutputStream ();

                // Create the info packet
                buffer = (new String ("0" + stream_name)).getBytes ();

                // Send 100 packets to make testing easier
                for (int i = 0; i < 100; i++)
                    {
                        // Send the packet
                        out.write (buffer);
                        System.out.println ("Sending: " + (new String (buffer)));

                        // Get the next packet to send
                        buffer = get_packet ();
                    }
                // Close connection gracefully
                sd.close ();
            }
        catch (IOException ioe)
            {
                System.out.println (ioe);
                ioe.printStackTrace ();
            }
    }

    //
    // Return the next packet to send
    //
    public byte[] get_packet ()
    {
        String   packet = "1";
        int      sample = 0;
        BytePort bp     = new BytePort (BytePort.Port5);

        // Send 5 samples per packet
        for (int i = 0; i < 5; i++)
            {
                // Get a sample from Port 5
                sample = bp.read ();

                // Get a timestamp and convert from ms to sec
                long time = System.currentTimeMillis () / 1000;

                // Add to packet
                packet = packet + Integer.toString (sample) + ":" + Long.toString (time) + "%";

                // Pause for 1 second
                try
                    {
                        Thread.sleep (1000);
                    }
                catch (InterruptedException ie) {}
            }

        return (packet.getBytes ());
    }

    //
    // Main
    //
    public static void main (String[] args)
    {
        // Run the client
        (new CLIENT (args[0], 4000, args[1])).run ();
    }
}
