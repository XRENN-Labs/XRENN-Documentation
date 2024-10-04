require 'net/http'
require 'uri'
require 'json'

TOKEN_URL = 'https://xrenn.ai/api/v1/auth_xrenn_token/obtain/'
REFRESH_URL = 'https://xrenn.ai/api/v1/auth_xrenn_token/refresh/'

def obtain_token(username, password)
  uri = URI.parse(TOKEN_URL)
  request = Net::HTTP::Post.new(uri)
  request.set_form_data("username" => username, "password" => password)

  response = Net::HTTP.start(uri.hostname, uri.port, use_ssl: uri.scheme == "https") do |http|
    http.request(request)
  end

  if response.code == '200'
    puts response.body
    JSON.parse(response.body)
  else
    puts "Error: #{response.code}, #{response.body}"
    nil
  end
end

def refresh_token(refresh)
  uri = URI.parse(REFRESH_URL)
  request = Net::HTTP::Post.new(uri)
  request.set_form_data("refresh" => refresh)

  response = Net::HTTP.start(uri.hostname, uri.port, use_ssl: uri.scheme == "https") do |http|
    http.request(request)
  end

  if response.code == '200'
    puts response.body
    JSON.parse(response.body)
  else
    puts "Error: #{response.code}, #{response.body}"
    nil
  end
end

# Example usage
obtain_token("your_username", "your_password")
refresh_token("your_refresh_token")