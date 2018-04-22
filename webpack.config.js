const path = require("path");
const outputDir = path.join(__dirname, "build/");

const isProd = process.env.NODE_ENV === "production";
const isDevServer = process.argv.some(v => v.includes("webpack-dev-server"));

module.exports = {
  entry: isDevServer
    ? [
        "webpack-dev-server/client?http://localhost:8080",
        "webpack/hot/only-dev-server",
        "./lib/es6/src/Index.bs.js"
      ]
    : ["./lib/es6/src/Index.bs.js"],
  mode: isProd ? "production" : "development",
  devtool: isProd ? false : "eval-source-map",
  output: {
    path: outputDir,
    publicPath: "/build/",
    filename: "Index.js"
  },
  devServer: {
    hot: true,
    publicPath: "/build/",
    watchOptions: {
      ignored: [/node_modules/, /build/]
    }
  }
};
