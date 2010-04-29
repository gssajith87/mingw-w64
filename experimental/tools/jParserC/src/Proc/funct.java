/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package Proc;
/**
 *
 * @author kecy7joy
 */
public class funct {
    private String Name;
    private String Ret;
    private String Args;

    public funct(final String in) {
        String tmp = in.replaceAll("\n", "");
        int open = tmp.lastIndexOf('(') + 1;
        int close = tmp.lastIndexOf(')');
        Args = tmp.substring(open,close).replaceAll("\\[[a-z].*[a-z]\\]", "").trim();
        iTokens i = new iTokens(tmp.substring(0, open - 1));
        Name = i.getName();
        Ret = i.getType();
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
        funct a = new funct("HRESULT GetObjectParam();");
        System.out.println(a.Ret);
        System.out.println(a.Name);
        System.out.println(a.Args);
        System.out.println();
        /*params p = new params(a.Args);
        System.out.println(p.getLstr(0));
        System.out.println(p.getLstr(1));*/
    }
}
