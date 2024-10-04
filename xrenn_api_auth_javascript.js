const axios = require('axios');

/**
 * The URL endpoint used to obtain an authentication token from the xrenn.ai API.
 *
 * This URL is used within the application to request and retrieve an authentication token,
 * which is necessary for accessing other endpoints within the xrenn.ai API.
 *
 * Example:
 * ```javascript
 * const response = await fetch(tokenUrl, {
 *   method: 'POST',
 *   body: JSON.stringify({ username: 'your-username', password: 'your-password' }),
 *   headers: { 'Content-Type': 'application/json' }
 * });
 * const data = await response.json();
 * ```
 */
const tokenUrl = 'https://xrenn.ai/api/v1/auth_xrenn_token/obtain/';

/**
 * The URL endpoint used for refreshing authentication tokens.
 * This URL points to the API responsible for providing a new authentication token in the system.
 *
 * @type {string}
 */
const refreshUrl = 'https://xrenn.ai/api/v1/auth_xrenn_token/refresh/';

/**
 * Fetches an authentication token using the provided username and password.
 *
 * @param {string} username - The username to authenticate.
 * @param {string} password - The password corresponding to the username.
 * @return {Promise<object|null>} The authentication token data are if successful, or null if an error occurs.
 */
async function obtainToken(username, password) {
    try {
        const response = await axios.post(tokenUrl, { username, password });
        return response.data;
    } catch (error) {
        console.error(`Error: ${error.response.status}, ${error.response.data}`);
        return null;
    }
}

/**
 * Sends a request to refresh the authentication token using a given refresh token.
 *
 * @param {string} refresh - The refresh token to be exchanged for a new authentication token.
 * @return {Promise<object|null>} The data from the response containing the new token if successful, or null if an error occurred.
 */
async function refreshToken(refresh) {
    try {
        const response = await axios.post(refreshUrl, { refresh });
        return response.data;
    } catch (error) {
        console.error(`Error: ${error.response.status}, ${error.response.data}`);
        return null;
    }
}