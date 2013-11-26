/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package edu.sju.ee.jni;

import java.io.IOException;

/**
 *
 * @author Leo
 */
public class LoadLibraryException extends IOException {

    public LoadLibraryException() {
    }

    public LoadLibraryException(String message) {
        super(message);
    }

    public LoadLibraryException(String message, Throwable cause) {
        super(message, cause);
    }

    public LoadLibraryException(Throwable cause) {
        super(cause);
    }

    
}
