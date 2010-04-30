/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package jparserc;

import java.awt.datatransfer.Clipboard;
import java.awt.datatransfer.ClipboardOwner;
import java.awt.datatransfer.Transferable;
import java.awt.datatransfer.StringSelection;
import java.awt.Toolkit;

/**
 *
 * @author Hirondelle Systems, 2010
 * License: BSD
 */
public final class Clipper implements ClipboardOwner {

    public void lostOwnership(Clipboard clipboard, Transferable contents) {
        //throw new UnsupportedOperationException("Not supported yet.");
    }

    public void setClipboardContents( String aString ){
    StringSelection stringSelection = new StringSelection( aString );
    Clipboard clipboard = Toolkit.getDefaultToolkit().getSystemClipboard();
    clipboard.setContents( stringSelection, this );
  }

}
