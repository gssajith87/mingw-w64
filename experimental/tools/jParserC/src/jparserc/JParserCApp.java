/*
 * JParserCApp.java
 */
package jparserc;

import java.io.*;
import org.jdesktop.application.Application;
import org.jdesktop.application.SingleFrameApplication;

/**
 * The main class of the application.
 */
public class JParserCApp extends SingleFrameApplication {

    private static String iInherits = null;
    private static String iName = null;
    private static String fn = null;
    private static String ifn = null;

    /**
     * At startup create and show the main frame of the application.
     */
    @Override
    protected void startup() {
        show(new JParserCView(this));
    }

    /**
     * This method is to initialize the specified window by injecting resources.
     * Windows shown in our application come fully initialized from the GUI
     * builder, so this additional configuration is not needed.
     */
    @Override
    protected void configureWindow(java.awt.Window root) {
    }

    /**
     * A convenient static getter for the application instance.
     * @return the instance of JParserCApp
     */
    public static JParserCApp getApplication() {
        return Application.getInstance(JParserCApp.class);
    }

    /**
     * Main method launching the application.
     */
    public static void main(String[] args) {
        if (args.length > 0) {
            if (parse(args)) {
                Process p = new Process();
                p.iName = iName;
                p.inh = iInherits;
                String in = readfile(ifn);
                if (p.ProcStr(in) == 0) {
                    p.proc();
                    if (fn == null) {
                        System.out.println(p.getDecl());
                    } else {
                        writefile(fn, p.getDecl());
                    }
                }
            } else {
                help(0, null);
            }
        } else {
            launch(JParserCApp.class, args);
        }
    }

    private static void writefile(String fna, String in) {
        try {
            FileWriter o = new FileWriter(fna);
            BufferedWriter out = new BufferedWriter(o);
            out.write(in);
            out.close();
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
        }
    }

    private static String readfile(String fna) {
        String ret = "";

        try {
            File file;
            FileInputStream fis = null;
            BufferedInputStream bis = null;
            InputStreamReader isr = null;
            BufferedReader bfr = null;
            String line;
            file = new File(fna);
            fis = new FileInputStream(file);
            bis = new BufferedInputStream(fis);
            isr = new InputStreamReader(bis);
            bfr = new BufferedReader(isr);
            while ((line = bfr.readLine()) != null) {
                ret += line;
                ret += "\n";
            }
        } catch (Exception e) {
            e.printStackTrace();
            System.exit(1);
        }
        return ret;
    }

    private static boolean parse(String[] args) {
        try {
            int i = 0;
            while (i < args.length) {
                if (args[i].startsWith("--")) {
                    if (args[i].equals("--inherits")) {
                        iInherits = args[i + 1];
                        i++;
                    }
                    if (args[i].equals("--interface")) {
                        iName = args[i + 1];
                        i++;
                    }
                    if (args[i].equals("--input")) {
                        ifn = args[i + 1];
                        i++;
                    }
                    if (args[i].equals("--output")) {
                        fn = args[i + 1];
                        i++;
                    }
                    if (args[i].equals("--helpt")) {
                        help(0, null);
                    }
                    i++;
                } else {
                    help(1, "Unknown argument " + args[i]);
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
            help(1, "Exception Occured.");
        }
        if (iName != null && ifn != null) {
            return true;
        } else {
            help(1, "Invalid Commands.");
        }

        return false;
    }

    private static void help(final int in, final String msg) {
        if (msg != null) System.err.println(msg);
        System.exit(in);
    }
}
