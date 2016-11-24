/* Copyright 2007 Theodore S. Norvell. All rights reserved.

 Redistribution and use in source and binary forms, with or without modification,
 are permitted provided that the following conditions are met:

   1. Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.
   2. Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.
   3. Neither the source nor binary form shall be included in any product used by
      or intended for use by any military organization. 

THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THEODORE
NORVELL BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

package monitor;

/** A final class for Monitors.
 * <P> Use an object of this class if you want to use delegation.
 * <P> Extend AbstractMonitor, if you want to use inheritance.
 * <P> The methods have the same meaning as in AbstractMonitor,
 * but here they are public.
 * @author Theodore S. Norvell
 * @version 1.0
 * @see AbstractMonitor
 */

public final class Monitor extends AbstractMonitor {

    private Assertion invariant ;

    public Monitor() {
        this( True_Assertion.singleton ) ; }

    public Monitor(Assertion invariant) {
        this.invariant = invariant ; }

    public Monitor(String name) {
        this( name, True_Assertion.singleton ) ; }

    public Monitor(String name, Assertion invariant) {
    	super(name) ;
        this.invariant = invariant ; }

    public boolean invariant() {
        return invariant.isTrue() ; }

    public void enter() {
        super.enter() ; }

    public void leave() {
        super.leave() ; }
    
    public<T> T leave( T result ) {
    	return super.leave( result ) ;  }

    public void doWithin( Runnable runnable ) {
    	super.doWithin( runnable ) ; }
    
    public<T> T doWithin( RunnableWithResult<T> runnable ) {
    	return super.doWithin( runnable ) ; }
    
    public Condition makeCondition() {
        return super.makeCondition() ; }

    public Condition makeCondition( Assertion assertion) {
        return super.makeCondition( assertion ) ; }
    
    public Condition makeCondition(String name) {
        return super.makeCondition(name) ; }

    public Condition makeCondition( String name, Assertion assertion) {
        return super.makeCondition( name, assertion ) ; }
}