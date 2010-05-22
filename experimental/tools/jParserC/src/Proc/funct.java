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
public class funct {
    private String Name;
    private String Ret;
    private String Args;

    public funct(final String in) {
        Args = "";
        String tmp = in.replaceAll("\n", "");
        int open = tmp.lastIndexOf('(') + 1;
        int close = tmp.lastIndexOf(')');
        StringTokenizer a = new StringTokenizer(tmp.substring(open,close),",");
        while (a.hasMoreTokens()) {
            Args += a.nextToken().replaceAll("\\[[a-z].*[a-z]\\]", "").trim();
            if (a.hasMoreTokens()) Args += ",";
        }
        iTokens i = new iTokens(tmp.substring(0, open - 1));
        Name = i.getName();
        Ret = i.getType().replace("__stdcall", "").trim();
    }

    public String getName() {
        return Name;
    }

    public String getRet() {
        return Ret;
    }

    public String getArgs() {
        return Args;
    }

    public static void main(String args[]) {
        funct a = new funct("HRESULT GetNames( \n" +
        "[out]  LPWSTR *pwszInterface, \n" +
        "[out]  LPWSTR *pwszMethod \n" +
        ");");
        System.out.println(a.Ret);
        System.out.println(a.Name);
        System.out.println(a.Args);
        System.out.println();
        /*params p = new params(a.Args);
        System.out.println(p.getLstr(0));
        System.out.println(p.getLstr(1));*/
    }
}
