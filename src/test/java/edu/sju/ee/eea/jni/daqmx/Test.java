package edu.sju.ee.eea.jni.daqmx;

import edu.sju.ee.eea.jni.daqmx.analog.in.measure.voltage.Acq_IntClk;
import java.util.logging.Level;
import java.util.logging.Logger;
import junit.framework.TestCase;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author Leo
 */
public class Test extends TestCase {

    public Test(String testName) {
        super(testName);
    }

    @Override
    protected void setUp() throws Exception {
        super.setUp();
    }

    @Override
    protected void tearDown() throws Exception {
        super.tearDown();
    }

    // TODO add test methods here. The name must begin with 'test'. For example:
    public void test() {
        new Acq_IntClk("T");
    }
}
