import java.net.HttpURLConnection
import java.net.URL
import java.io.BufferedReader
import java.io.InputStreamReader
import java.io.OutputStream

const val TOKEN_URL = "https://xrenn.ai/api/v1/auth_xrenn_token/obtain/"
const val REFRESH_URL = "https://xrenn.ai/api/v1/auth_xrenn_token/refresh/"

fun sendPostRequest(url: String, params: String): String {
    val url = URL(url)
    val conn = url.openConnection() as HttpURLConnection
    conn.requestMethod = "POST"
    conn.doOutput = true

    val outputStream: OutputStream = conn.outputStream
    outputStream.write(params.toByteArray())
    outputStream.flush()
    outputStream.close()

    val responseCode: Int = conn.responseCode
    println("Response Code: $responseCode")

    val response = BufferedReader(InputStreamReader(conn.inputStream))
    val responseStrBuilder = StringBuilder()
    response.forEachLine { responseStrBuilder.append(it) }
    response.close()

    return responseStrBuilder.toString()
}

fun obtainToken(username: String, password: String) {
    val params = "username=$username&password=$password"
    val response = sendPostRequest(TOKEN_URL, params)
    println("Response: $response")
}

fun refreshToken(refresh: String) {
    val params = "refresh=$refresh"
    val response = sendPostRequest(REFRESH_URL, params)
    println("Response: $response")
}

fun main() {
    obtainToken("your_username", "your_password")
    refreshToken("your_refresh_token")
}