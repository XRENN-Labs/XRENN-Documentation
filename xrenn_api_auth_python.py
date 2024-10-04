"""
This script contains functions to get and refresh the authentication token for the XRENN™ API.
The functions use the 'requests' library to send HTTP requests to the XRENN™ API.
The functions return a dictionary with the authentication token if the request is successful; otherwise, None.

The functions are:
    - obtain_token(username, password): Get the authentication token.
    - refresh_token(refresh): Refresh the authentication token.

The functions are used in the following way:
    - Obtain the authentication token:
        token = obtain_token(username, password)
    - Refresh the authentication token:
        token = refresh_token(refresh)
"""
import requests


# The URL to get the authentication token.
token_url = "https://xrenn.ai/api/v1/auth_xrenn_token/obtain/"
refresh_url = "https://xrenn.ai/api/v1/auth_xrenn_token/refresh/"


# The URL to refresh the authentication token.
def obtain_token(username, password):
    """
    :param username: The username required authenticating the user.
    :param password: The password is required to authenticate the user.
    :return: A dictionary containing the authentication token if the request is successful; otherwise, None.
    """
    response = requests.post(token_url, data={"username": username, "password": password})
    if response.status_code == 200:
        return response.json()
    else:
        print(f"Error: {response.status_code}, {response.json()}")
        return None


# The URL to refresh the authentication token.
def refresh_token(refresh):
    """
    :param refresh: the refresh token used to request a new access token.
    :type refresh: str
    :return: A JSON response with a new access token if the request is successful, or None if it fails.
    :rtype: dict or None
    """
    response = requests.post(refresh_url, data={"refresh": refresh})
    if response.status_code == 200:
        return response.json()
    else:
        print(f"Error: {response.status_code}, {response.json()}")
        return None
