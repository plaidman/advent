module.exports = {
    parser: "@typescript-eslint/parser",
    plugins: [
        "@typescript-eslint/eslint-plugin",
    ],
    parserOptions: {
        project: './tsconfig.json',
    },
    extends: [
        "eslint:recommended",
        "plugin:@typescript-eslint/recommended",
        "plugin:@typescript-eslint/recommended-requiring-type-checking",
        "prettier",
    ],
    rules: {
    },
};