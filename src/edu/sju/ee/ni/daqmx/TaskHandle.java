/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package edu.sju.ee.ni.daqmx;

import edu.sju.ee98.ni.daqmx.NativeUtils;
import edu.sju.ee98.ni.daqmx.analog.ContGenIntClk;
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author Leo
 */
public class TaskHandle {

    static {
        try {
            NativeUtils.loadLibraryFromJar("libDAQ");
        } catch (IOException ex) {
            Logger.getLogger(ContGenIntClk.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    private long nativeStruct;

    private native long nTaskHandle(String taskName);

    public TaskHandle(String taskName) {
        nativeStruct = nTaskHandle(taskName);
    }

    private native void nfinalize(long nativeStruct);

    @Override
    protected void finalize() throws Throwable {
        this.nfinalize(nativeStruct);
        super.finalize();
    }

    //Test----------------------------------------------------------------------
    private native void test(long nativeStruct);

    public static void main(String[] args) {
        TaskHandle taskHandle = new TaskHandle("");
        taskHandle.test(taskHandle.nativeStruct);
    }

}
