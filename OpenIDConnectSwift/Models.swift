/** Author: Jordan Melberg **/

/** Copyright © 2016, Okta, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import Foundation

class OktaConfiguration {
    let kIssuer: String!
    let kClientID: String!
    let kRedirectURI: String!
    let kAppAuthExampleAuthStateKey: String!
    let apiEndpoint: NSURL!
    
    init(){
        kIssuer = "https://example.oktapreview.com"                             // Base url of Okta Developer domain
        kClientID = "79arVRKBcBEYMuMOXrYF"                                      // Client ID of Application
        kRedirectURI = "com.oktapreview.example:/oauth"                         // Reverse DNS notation of base url with oauth route
        kAppAuthExampleAuthStateKey = "com.okta.openid.authState"
        apiEndpoint = NSURL(string: "https://example.com/protected")            // Resource Server URL
    }
}
