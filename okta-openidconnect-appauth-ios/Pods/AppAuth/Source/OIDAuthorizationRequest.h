/*! @file OIDAuthorizationRequest.h
    @brief AppAuth iOS SDK
    @copyright
        Copyright 2015 Google Inc. All Rights Reserved.
    @copydetails
        Licensed under the Apache License, Version 2.0 (the "License");
        you may not use this file except in compliance with the License.
        You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

        Unless required by applicable law or agreed to in writing, software
        distributed under the License is distributed on an "AS IS" BASIS,
        WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
        See the License for the specific language governing permissions and
        limitations under the License.
 */

#import <Foundation/Foundation.h>

// These files only declare string constants useful for constructing a @c OIDAuthorizationRequest,
// so they are imported here for convenience.
#import "OIDResponseTypes.h"
#import "OIDScopes.h"

@class OIDServiceConfiguration;

NS_ASSUME_NONNULL_BEGIN

/*! @brief The @c code_challenge_method  value for the S256 code challenge.
    @see https://tools.ietf.org/html/rfc7636#section-4.3
 */
extern NSString *const OIDOAuthorizationRequestCodeChallengeMethodS256;


/*! @class OIDAuthorizationRequest
    @brief Represents an authorization request.
    @see https://tools.ietf.org/html/rfc6749#section-4
    @see https://tools.ietf.org/html/rfc6749#section-4.1.1
 */
@interface OIDAuthorizationRequest : NSObject <NSCopying, NSSecureCoding>

/*! @property configuration
    @brief The service's configuration.
    @remarks This configuration specifies how to connect to a particular OAuth provider.
        Configurations may be created manually, or via an OpenID Connect Discovery Document.
 */
@property(nonatomic, readonly) OIDServiceConfiguration *configuration;

/*! @property responseType
    @brief The expected response type.
    @remarks response_type
    @discussion Generally 'code' if pure OAuth, otherwise a space-delimited list of of response
        types including 'code', 'token', and 'id_token' for OpenID Connect.
    @see https://tools.ietf.org/html/rfc6749#section-3.1.1
    @see http://openid.net/specs/openid-connect-core-1_0.html#rfc.section.3
 */
@property(nonatomic, readonly) NSString *responseType;

/*! @property clientID
    @brief The client identifier.
    @remarks client_id
    @see https://tools.ietf.org/html/rfc6749#section-2.2
 */
@property(nonatomic, readonly) NSString *clientID;

/*! @property scope
    @brief The value of the scope parameter is expressed as a list of space-delimited,
        case-sensitive strings.
    @remarks scope
    @see https://tools.ietf.org/html/rfc6749#section-3.3
 */
@property(nonatomic, readonly, nullable) NSString *scope;

/*! @property redirectURL
    @brief The client's redirect URI.
    @remarks redirect_uri
    @see https://tools.ietf.org/html/rfc6749#section-3.1.2
 */
@property(nonatomic, readonly) NSURL *redirectURL;

/*! @property state
    @brief An opaque value used by the client to maintain state between the request and callback.
    @remarks state
    @discussion If this value is not explicitly set, this library will automatically add state and
        perform appropriate validation of the state in the authorization response. It is recommended
        that the default implementation of this parameter be used wherever possible. Typically used
        to prevent CSRF attacks, as recommended in RFC6819 Section 5.3.5.
    @see https://tools.ietf.org/html/rfc6749#section-4.1.1
    @see https://tools.ietf.org/html/rfc6819#section-5.3.5
 */
@property(nonatomic, readonly, nullable) NSString *state;

/*! @property codeVerifier
    @brief The PKCE code verifier.
    @remarks code_verifier
    @discussion The code verifier itself is not included in the authorization request that is sent
        on the wire, but needs to be in the token exchange request.
        @c OIDAuthorizationResponse.tokenExchangeRequest will create a @c OIDTokenRequest that
        includes this parameter automatically.
    @see https://tools.ietf.org/html/rfc7636#section-4.1
 */
@property(nonatomic, readonly, nullable) NSString *codeVerifier;

/*! @property codeChallenge
    @brief The PKCE code challenge, derived from #codeVerifier.
    @remarks code_challenge
    @see https://tools.ietf.org/html/rfc7636#section-4.2
 */
@property(nonatomic, readonly, nullable) NSString *codeChallenge;

/*! @property codeChallengeMethod
    @brief The method used to compute the @c #codeChallenge
    @remarks code_challenge_method
    @see https://tools.ietf.org/html/rfc7636#section-4.3
 */
@property(nonatomic, readonly, nullable) NSString *codeChallengeMethod;

/*! @property additionalParameters
    @brief The client's additional authorization parameters.
    @see https://tools.ietf.org/html/rfc6749#section-3.1
 */
@property(nonatomic, readonly, nullable) NSDictionary<NSString *, NSString *> *additionalParameters;

/*! @fn init
    @internal
    @brief Unavailable. Please use
        @c initWithConfiguration:clientId:scopes:redirectURL:additionalParameters:.
 */
- (nullable instancetype)init NS_UNAVAILABLE;

/*! @fn initWithConfiguration:clientId:scopes:redirectURL:responseType:additionalParameters:
    @brief Creates an authorization request with opinionated defaults (a secure @c state, and
        PKCE with S256 as the @c code_challenge_method).
    @param configuration The service's configuration.
    @param clientID The client identifier.
    @param scopes An array of scopes to combine into a single scope string per the OAuth2 spec.
    @param redirectURL The client's redirect URI.
    @param responseType The expected response type.
    @param additionalParameters The client's additional authorization parameters.
    @remarks This convenience initializer generates a state parameter and PKCE challenges
        automatically.
 */
- (nullable instancetype)initWithConfiguration:(OIDServiceConfiguration *)configuration
                clientId:(NSString *)clientID
                  scopes:(nullable NSArray<NSString *> *)scopes
             redirectURL:(NSURL *)redirectURL
            responseType:(NSString *)responseType
    additionalParameters:(nullable NSDictionary<NSString *, NSString *> *)additionalParameters;

/*! @fn initWithConfiguration:clientId:scope:redirectURL:responseType:state:codeVerifier:codeChallenge:codeChallengeMethod:additionalParameters:
    @brief Designated initializer.
    @param configuration The service's configuration.
    @param clientID The client identifier.
    @param scope A scope string per the OAuth2 spec (a space-delimited set of scopes).
    @param redirectURL The client's redirect URI.
    @param responseType The expected response type.
    @param state An opaque value used by the client to maintain state between the request and
        callback.
    @param codeVerifier The PKCE code verifier. See @c OIDAuthorizationRequest.generateCodeVerifier.
    @param codeChallenge The PKCE code challenge, calculated from the code verifier such as with
        @c OIDAuthorizationRequest.codeChallengeS256ForVerifier:.
    @param codeChallengeMethod The PKCE code challenge method.
        ::OIDOAuthorizationRequestCodeChallengeMethodS256 when
        @c OIDAuthorizationRequest.codeChallengeS256ForVerifier: is used to create the code
        challenge.
    @param additionalParameters The client's additional authorization parameters.
 */
- (nullable instancetype)initWithConfiguration:(OIDServiceConfiguration *)configuration
                clientId:(NSString *)clientID
                   scope:(nullable NSString *)scope
             redirectURL:(NSURL *)redirectURL
            responseType:(NSString *)responseType
                   state:(nullable NSString *)state
            codeVerifier:(nullable NSString *)codeVerifier
           codeChallenge:(nullable NSString *)codeChallenge
     codeChallengeMethod:(nullable NSString *)codeChallengeMethod
    additionalParameters:(nullable NSDictionary<NSString *, NSString *> *)additionalParameters
    NS_DESIGNATED_INITIALIZER;

/*! @fn authorizationRequestURL
    @brief Constructs the request URI by adding the request parameters to the query component of the
        authorization endpoint URI using the "application/x-www-form-urlencoded" format.
    @return A URL representing the authorization request.
    @see https://tools.ietf.org/html/rfc6749#section-4.1.1
 */
- (NSURL *)authorizationRequestURL;

/*! @fn generateState
    @brief Generates an OAuth state param using a random source.
    @return The generated state.
    @see https://tools.ietf.org/html/rfc6819#section-5.3.5
 */
+ (nullable NSString *)generateState;

/*! @fn generateCodeVerifier
    @brief Constructs a PKCE-compliant code verifier.
    @return The generated code verifier.
    @see https://tools.ietf.org/html/rfc7636#section-4.1
 */
+ (nullable NSString *)generateCodeVerifier;

/*! @fn codeChallengeS256ForVerifier:
    @brief Creates a PKCE S256 codeChallenge from the codeVerifier.
    @param codeVerifier The code verifier from which the code challenge will be derived.
    @return The generated code challenge.
    @details Generate a secure code verifier to pass into this method with
        @c OIDAuthorizationRequest.generateCodeVerifier. The matching @c #codeChallengeMethod for
        @c #codeChallenge%s created by this method is
        ::OIDOAuthorizationRequestCodeChallengeMethodS256.
    @see https://tools.ietf.org/html/rfc7636#section-4.1
 */
+ (nullable NSString *)codeChallengeS256ForVerifier:(nullable NSString *)codeVerifier;

@end

NS_ASSUME_NONNULL_END
