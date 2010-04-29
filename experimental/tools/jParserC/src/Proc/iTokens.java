/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package Proc;
import java.util.StringTokenizer;

/**
 *
 * @author kecy7joy
 */
public class iTokens {
    private String Type;
    private String Name;
    private java.util.List<String> lstr;

    public String getName() {
        return Name.trim();
    }

    public String getType() {
        return Type.trim();
    }

    private iTokens() {
        lstr = new java.util.ArrayList<String>();
        Type = "";
        Name = "";
    }

    public iTokens(final String in) {
        this();
        String cleaned = in.replaceAll("\\[[a-z].*[a-z]\\]", "");
        StringTokenizer toks;
        if (in.contains("*")) {
            toks = new StringTokenizer(cleaned, "*", true);
        } else {
            toks = new StringTokenizer(cleaned);
        }

        while(toks.hasMoreTokens()) {
            lstr.add(toks.nextToken());
        }

        for (int i = lstr.size() - 1; i > 0; i--) {
            //System.out.println(i);
            //System.out.println(lstr.get(i - 1));
            if (lstr.get(i - 1).trim().charAt(lstr.get(i - 1).trim().length() - 1) == '*')
                Type = lstr.get(i - 1).trim() + Type;
            else
                Type = lstr.get(i - 1).trim() + " " + Type;
        }
        Name = lstr.get(lstr.size() - 1);
    }

    public static void main(String args[]) {
        iTokens lsa = new iTokens("[in, optional] const D2D1_COLOR_F *clearColor");
        System.out.println(lsa.getType());
        System.out.println(lsa.getName());
    }
}
