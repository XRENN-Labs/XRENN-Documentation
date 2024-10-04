using System;
using System.Net.Http;
using System.Collections.Generic;
using System.Threading.Tasks;
using Newtonsoft.Json;

public class Program
{
    private static readonly string tokenUrl = "https://xrenn.ai/api/v1/auth_xrenn_token/obtain/";
    private static readonly string refreshUrl = "https://xrenn.ai/api/v1/auth_xrenn_token/refresh/";

    public static async Task<Dictionary<string, string>> ObtainTokenAsync(string username, string password)
    {
        using (HttpClient client = new HttpClient())
        {
            var data = new Dictionary<string, string>
            {
                { "username", username },
                { "password", password }
            };

            var response = await client.PostAsync(tokenUrl, new FormUrlEncodedContent(data));
            var responseString = await response.Content.ReadAsStringAsync();

            if (response.IsSuccessStatusCode)
            {
                return JsonConvert.DeserializeObject<Dictionary<string, string>>(responseString);
            }
            else
            {
                Console.WriteLine($"Error: {response.StatusCode}, {responseString}");
                return null;
            }
        }
    }

    public static async Task<Dictionary<string, string>> RefreshTokenAsync(string refresh)
    {
        using (HttpClient client = new HttpClient())
        {
            var data = new Dictionary<string, string>
            {
                { "refresh", refresh }
            };

            var response = await client.PostAsync(refreshUrl, new FormUrlEncodedContent(data));
            var responseString = await response.Content.ReadAsStringAsync();

            if (response.IsSuccessStatusCode)
            {
                return JsonConvert.DeserializeObject<Dictionary<string, string>>(responseString);
            }
            else
            {
                Console.WriteLine($"Error: {response.StatusCode}, {responseString}");
                return null;
            }
        }
    }
}