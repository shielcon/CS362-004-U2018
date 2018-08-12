

import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!


public class UrlValidatorTest extends TestCase {

   public UrlValidatorTest(String testName) {
      super(testName);
   }

   //manual tests of isValid
   public void testManualTest()
   {

		UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		
		assertFalse(urlVal.isValid("www.facebook.com")); //No scheme
	  
		if (!urlVal.isValid("http://www.facebook.com/"))
			System.out.println("manual test 1 failed");
		if (urlVal.isValid("www.facebookcom"))
			System.out.println("manual test 2 failed");
		if (urlVal.isValid("facebook.com"))
			System.out.println("manual test 3 failed");
		if (!urlVal.isValid("http://www.facebook.com"))
			System.out.println("manual test 4 failed");
		if (!urlVal.isValid("http://www.TWITTER.com"))
			System.out.println("manual test 5 failed");
		if (urlVal.isValid("Facebook"))
			System.out.println("manual test 6 failed");
		if (urlVal.isValid("www.facebook.com/google.com"))
			System.out.println("manual test 7 failed");
		if (!urlVal.isValid("ftp://www.facebook.com"))
			System.out.println("manual test 8 failed");
		if (urlVal.isValid("www.facebook.com:255"))
			System.out.println("manual test 9 failed");
		if (urlVal.isValid("asffewersderfef/s"))
			System.out.println("manual test 10 failed");
		if (urlVal.isValid("www.facebook.com"))
			System.out.println("manual test 11 failed");
		if (!urlVal.isValid("https://www.google.com/search?source=hp&ei=A7hoW4GhE4y80PEP2bmymA0&q=news&oq=news&gs_l=psy-ab.3..0i131k1l2j0j0i131k1j0j0i131k1j0l2j0i131k1j0.1076.1457.0.1614.5.4.0.0.0.0.150.391.0j3.3.0....0...1.1.64.psy-ab..2.3.390.0...0.MFyR9PjJ_YA"))
			System.out.println("manual test 12 failed");

   }
   
   //Tests good input partitions
   public void testYourFirstPartition()
   {
	   
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   //good input partitioning
	  if (!urlVal.isValid("http://www.google.com/parentDir/childDir:80?foo=bar"))//fails
		  System.out.println("Good partition 1 failed");
	  if (!urlVal.isValid("http://www.google.com/parentDir/childDir?foo=bar"))//fails
		  System.out.println("Good partition 2 failed");
	  if (!urlVal.isValid("http://www.google.com/parentDir/childDir:80"))//fails
		  System.out.println("Good partition 3 failed");
	  if (!urlVal.isValid("http://www.google.com/parentDir/somethingElse"))
		  System.out.println("Good partition 4 failed");
	   
	   if (!urlVal.isValid("http://www.google.com/parentDir:80?foo=bar"))//succeeds
		   System.out.println("Good partition 5 failed");
	   if (!urlVal.isValid("http://www.google.com/parentDir:80?foo=bar&true=that"))//succeeds
		   System.out.println("Good partition 6 failed");
	   if (!urlVal.isValid("http://www.google.com/parentDir?foo=bar"))//succeeds
		   System.out.println("Good partition 7 failed");
	   if (!urlVal.isValid("http://www.google.com/parentDir:80"))//succeeds
		   System.out.println("Good partition 8 failed");
	   
	   if (!urlVal.isValid("http://www.google.com:80?foo=bar"))//fails
		   System.out.println("Good partition 9 failed");
	   if (!urlVal.isValid("http://www.google.com/:80?foo=bar"))
		   System.out.println("Good partition 10 failed");
	   if (!urlVal.isValid("http://www.google.com/?foo=bar"))
		   System.out.println("Good partition 11 failed");
	   if (!urlVal.isValid("http://www.google.com:80"))//fails
		   System.out.println("Good partition 12 failed");
	   if (!urlVal.isValid("http://www.google.com"))
		   System.out.println("Good partition 13 failed");
	   

   }
   
   //Tests bad input partitions
   public void testYourSecondPartition(){
	   
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   if (urlVal.isValid("www.google.com"))
		   System.out.println("Bad partition 1 failed");
	   if (urlVal.isValid("www.google.com/"))
		   System.out.println("Bad partition 2 failed");
	   if (urlVal.isValid("www.google.com:80"))
		   System.out.println("Bad partition 3 failed");
	   if (urlVal.isValid("www.google.com?foo=bar"))
		   System.out.println("Bad partition 4 failed");
	   if (urlVal.isValid("www.google.com:80?foo=bar"))
		   System.out.println("Bad partition 5 failed");
	   
	   if (urlVal.isValid("http://google.com:?query=query"))
		   System.out.println("Bad partition 6 failed");
	   if (urlVal.isValid("http://www.google.com:noPortNum"))
		   System.out.println("Bad partition 7 failed");
	   
   }
   
   //programmatic test cases
   public void testIsValid()
   {
	   
	    UrlValidator validator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);


        String[] firstUrlPart = {"http://", "ftp://", "ftp:/", "ftp:", "://", ""};
        Boolean[] firstUrlPartValidity = {true, true, false, false, false, true};
        String[] urlDomains = {"google.com", "google.co.uk", "127.0.0.1", "google.haha", ".g.G.g.", "google.io"};
        Boolean[] urlDomainsValidity = {true, true, true, false, false, true};
        String[] urlPorts = {"", ":5000", ":5", "5000000", ":haha" };
        Boolean[] urlPortsValidity = {true ,true, true, false, false};
        String[] urlPaths = {"","/", "/hello", "/hello/", "../hello/"};
        Boolean[] urlPathsValidity = {true, true, true, true, false};
        //Test allow2slash, noFragment
        String[] urlQuerys = {"?haha=hello&answer=question", "?haha=hello", ""};
        Boolean[] urlQuerysValidity = {true, true, true};
        for(int firstPartIndex = 0; firstPartIndex < firstUrlPart.length - 1; firstPartIndex++){
            String firstUrlString = firstUrlPart[firstPartIndex];
            Boolean firstUrlValid = firstUrlPartValidity[firstPartIndex];
            System.out.println("Test Case");
            for(int urlDomainIndex = 0; urlDomainIndex < urlDomains.length - 1; urlDomainIndex++){
                String urlDomainString = urlDomains[urlDomainIndex];
                Boolean urlDomainValid = urlDomainsValidity[urlDomainIndex];
                for(int urlPortIndex = 0; urlPortIndex < urlPorts.length - 1; urlPortIndex++) {
                    String urlPortString = urlPorts[urlPortIndex];
                    Boolean urlPortValid = urlPortsValidity[urlPortIndex];
                    for(int urlPathIndex = 0; urlPathIndex < urlPaths.length - 1; urlPathIndex++) {
                        String urlPathString = urlPaths[urlPathIndex];
                        Boolean urlPathValid = urlPathsValidity[urlPathIndex];
                        for(int urlQueryIndex = 0; urlQueryIndex < urlQuerys.length - 1; urlQueryIndex++) {
                            String urlQueryString = urlQuerys[urlQueryIndex];
                            Boolean urlQueryValid = urlQuerysValidity[urlQueryIndex];
                            Boolean urlValid = firstUrlValid && urlDomainValid && urlPortValid && urlPathValid
                                    && urlQueryValid;

                            if(urlValid){
                                System.out.print("Test Case for valid url: ");
                            }
                            else{
                                System.out.print("Test Case for invalid url: ");
                            }
                            String url = firstUrlString + urlDomainString + urlPortString + urlPathString +
                                    urlQueryString;
                            Boolean urlValidTest = validator.isValid(url);
                            System.out.println(url);
                            //assertTrue(urlValid == urlValidTest);
                            if(urlValid == urlValidTest){
                                System.out.println("Test Case PASSED");
                            }
                            else{
                                System.out.println("Test Case FAILED");
                            }
                        }
                    }
                }
            }
   
        }
   }
   
   public static void main(String[] argv) {
	   
	   UrlValidatorTest urlTest = new UrlValidatorTest("test");
	   
	   urlTest.testIsValid();
	   urlTest.testYourFirstPartition();
	   urlTest.testYourSecondPartition();
	   urlTest.testManualTest();

	   
   }

}










