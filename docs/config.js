var mermaidId = 0;
mermaid.initialize({
  startOnLoad: false,
  securityLevel: "loose",
  flowchart: {
    curve: "basis",
    htmlLabels: false,
  },
});
window.$docsify = {
  repo: "https://github.com/fredericbonnet/picotest",
  themeColor: "#019CB7",
  auto2top: true,
  themeable: {
    readyTransition: true,
  },
  markdown: {
    renderer: {
      code: function (code, lang) {
        try {
          if (lang === "mermaid") {
            return (
              '<div class="mermaid">' +
              mermaid.render("mermaid-svg-" + mermaidId++, code) +
              "</div>"
            );
          }
        } catch (e) {
          /* ignore */
        }
        return this.origin.code.apply(this, arguments);
      },
    },
  },
};
