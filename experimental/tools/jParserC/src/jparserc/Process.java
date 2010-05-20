/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package jparserc;

import java.util.*;
import Proc.*;

/**
 *
 * @author kecy7joy
 */
public class Process {

    List<funct> funts = new ArrayList<funct>();
    List<String> strs = new ArrayList<String>();
    String iName;
    String inh;

    void proc() {
        for (int i = 0; i < strs.size(); i++) {
            funts.add(new funct(strs.get(i)));
        }
    }

    private boolean comparestrs(final String in) {
        for (int i = 0; i < strs.size(); i++) {
            funct f = new funct(strs.get(i));
            if (in.compareTo(f.getName()) == 0) {
                return false;
            }
        }
        return true;
    }

    int ProcStr(String in) {
        int index = 0;
        boolean parsed = false;
        funct f = null;
        while (!parsed || in.indexOf("\n\n", index) != -1) {
            parsed = true;
            int next = in.indexOf("\n\n", index + 1);
            if (index == -1) {
                break;
            }
            String str = in.substring(index, (next == -1 ? in.length() - 1 : next));
            index = next;
            if (str.length() == 0) {
                return 1;
            }
            try {
                f = new funct(str);
            } catch (Exception e) {
                e.printStackTrace();
                return 1;
            }
            if (comparestrs(f.getName())) {
                strs.add(str);
            } else {
                return 2;
            }
        }
        return 0;
    }

    String fwd() {
        String ret;
        String mac = "__" + iName + "_FWD_DEFINED__";
        ret = "#infdef " + mac + "\n";
        ret += "#define " + mac + "\n";
        ret += "typedef struct " + iName + " " + iName + ";\n";
        ret += "#endif";
        return ret;
    }

    String Suffix() {
        String ret;
        ret = "#endif /*defined(__cplusplus) && !defined(CINTERFACE)*/\n";
        ret += "#endif /*__" + iName + "_INTERFACE_DEFINED__*/\n";
        return ret;
    }

    String cMac() {
        String ret;
        //String iName = jTextField1.getText().trim();
        ret = "#ifdef COBJMACROS\n";
        for (int i = 0; i < funts.size(); i++) {
            String args = "This";
            funct f = funts.get(i);
            ret += "#define " + iName + "_" + f.getName() + "(";
            params p = new params(f.getArgs());
            if (!p.getLstr().isEmpty()) {
                args += ",";
                for (int j = 0; j < p.getLstr().size(); j++) {
                    iTokens t = new iTokens(p.getLstr(j));
                    args += t.getName();
                    if (j + 1 != p.getLstr().size()) {
                        args += ",";
                    }
                }
                ret += args;
            }
            ret += ") ";
            ret += "(This)->lpVtbl->" + f.getName() + "(" + args + ")\n";
        }
        ret += "#endif /*COBJMACROS*/\n";
        return ret;
    }

    String cVtbl() {
        String ret;
        //String iName = jTextField1.getText().trim();
        String structname = iName + "Vtbl";
        ret = "typedef struct " + structname + " {\n";
        ret += "  BEGIN_INTERFACE\n";
        for (int i = 0; i < funts.size(); i++) {
            funct f = funts.get(i);
            ret += "    " + f.getRet();
            ret += " (WINAPI *" + f.getName() + ")(";
            ret += iName + " *This";
            params p = new params(f.getArgs().trim());
            if (!p.getLstr().isEmpty()) {
                ret += ",";
                for (int j = 0; j < p.getLstr().size(); j++) {
                    ret += p.getLstr(j);
                    if (j + 1 != p.getLstr().size()) {
                        ret += ",";
                    }
                }
            }
            ret += ");\n";
        }
        ret += "  END_INTERFACE\n";
        ret += "} " + structname + ";\n";
        ret += "struct " + iName + " {\n";
        ret += "  CONST_VTBL struct " + structname + " *lpVtbl;\n};\n";
        return ret;
    }

    String midfix() {
        String ret;
        ret = "#else /*defined(__cplusplus) && !defined(CINTERFACE)*/\n";
        return ret;
    }

    String Prefix() {
        //String iName = jTextField1.getText().trim();

        String defs = "__" + iName + "_INTERFACE_DEFINED__";
        String ret = "#ifndef " + defs + "\n";
        ret += "#define " + defs + "\n";
        ret += "typedef " + iName + " *LP" + iName.toUpperCase() + "\n";
        ret += "#if defined(__cplusplus) && !defined(CINTERFACE)\n";
        ret += "DECLARE_INTERFACE_(" + iName;
        if (inh != null && !inh.isEmpty()) {
            ret += "," + inh;
        }
        ret += ") {\n";
        return ret;
    }

    String sHeader() {
        String ret = "#undef  INTERFACE\n";
        ret += "#define INTERFACE " + iName + "\n";
        ret += "DECLARE_INTERFACE_(" + iName;
        if (inh != null && !inh.isEmpty()) {
            ret += "," + inh;
        } else {
            ret += ",IUnknown";
        }
        ret += ")\n{\n    BEGIN_INTERFACE\n";
        return ret;
    }

    String sUnknown() {
        String ret = "\n    /* IUnknown methods */\n";
        ret += "    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void **ppvObject) PURE;\n";
        ret += "    STDMETHOD_(ULONG, AddRef)(THIS) PURE;\n";
        ret += "    STDMETHOD_(ULONG, Release)(THIS) PURE;\n";
        return ret;
    }

    String scppVtabl() {
        String ret = "";
        ret += "\n    /* " + iName + " methods */\n";
        for (int i = 0; i < funts.size(); i++) {
            funct f = funts.get(i);
            ret += "    STDMETHOD";
            if (!f.getRet().equals("void")) {
                ret += "_(" + f.getRet() + ",";
            } else {
                ret += "(";
            }
            ret += f.getName() + ")(THIS";
            if (!f.getArgs().isEmpty()) {
                ret += "_ ";
                params p = new params(f.getArgs());
                for (int j = 0; j < p.getLstr().size(); j++) {
                    ret += p.getLstr(j);
                    if (j + 1 != p.getLstr().size()) {
                        ret += ",";
                    }
                }
            }
            ret += ") PURE;\n";
        }
        return ret;
    }

    String sfooter() {
        return "\n    END_INTERFACE\n};";
    }

    String cppVtbl() {
        String ret = "";
        for (int i = 0; i < funts.size(); i++) {
            funct f = funts.get(i);
            ret += "  virtual " + f.getRet() + " WINAPI ";
            ret += f.getName();
            params p = new params(f.getArgs());
            ret += "(";
            for (int j = 0; j < p.getLstr().size(); j++) {
                ret += p.getLstr(j);
                if (j + 1 != p.getLstr().size()) {
                    ret += ",";
                }
            }
            ret += ") PURE;\n";
        }
        ret += "};\n";
        return ret;
    }

    String getDecl() {
        String str;
        str = fwd();
        str += "\n\n\n\n\n";
        str += Prefix();
        str += cppVtbl();
        str += midfix();
        str += cVtbl();
        str += cMac();
        str += Suffix();
        str += "\n";
        return str;
    }

    String simple() {
        String ret = sHeader();
        ret += sUnknown();
        if (!iName.equals("IUnknown"))
        ret += scppVtabl();
        ret += sfooter();
        return ret;
    }
}
