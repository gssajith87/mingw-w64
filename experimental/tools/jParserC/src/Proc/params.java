/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package Proc;
import java.util.*;

/**
 *
 * @author kecy7joy
 */
public class params {
    private List<String> lstr;

    private params(){
        lstr = new ArrayList<String>();
    }

    public params(final String in) {
        this();
        String tmp = in.replaceAll("\n", "").replaceAll("\\[[a-z].*[a-z]\\]", "");
        StringTokenizer toks = new StringTokenizer(tmp,",");
        while (toks.hasMoreTokens()) {
            lstr.add(toks.nextToken().trim());
        }
    }

    public List<String> getLstr() {
        return lstr;
    }

    public String getLstr(final int i) {
        return lstr.get(i);
    }

    public static void main(String arggs[]) {
        List<iTokens> l = new ArrayList<iTokens>();

        params p = new params("[in, out, optional]  IMFMediaBuffer *pIHeader, DWORD *pcbHeader");

        for (int i = 0; i < p.getLstr().size(); i++) {
            System.out.println("Adding " + p.getLstr(i));
            l.add(new iTokens(p.getLstr(i)));
        }

        for (int i = 0; i < l.size(); i++) {
            System.out.println("line " + String.valueOf(i) + ": ");
            System.out.print("Type: " + l.get(i).getType());
            System.out.print("Name: " + l.get(i).getName());
            System.out.println();
        }
    }
}
