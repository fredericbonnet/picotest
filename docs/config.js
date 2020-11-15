var mermaidId = 0;
mermaid.initialize({
  startOnLoad: false,
  securityLevel: "loose",
  flowchart: {
    curve: "basis",
    htmlLabels: false,
  },
});
function renderMermaid(code, link) {
  // Generate Mermaid SVG into container
  const div = document.createElement("div");
  div.className = "mermaid";
  div.innerHTML = mermaid.render("mermaid-svg-" + mermaidId++, code);

  // Convert SVG links to docsify format
  const div2 = document.createElement("div");
  div.querySelectorAll("a.clickable").forEach((a) => {
    div2.innerHTML = link(a.getAttribute("href"));
    a.setAttribute("href", div2.firstChild.getAttribute("href"));
  });

  return div.outerHTML;
}
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
            return renderMermaid(code, this.origin.link);
          }
        } catch (e) {
          /* ignore */
        }
        return this.origin.code.apply(this, arguments);
      },
    },
  },
};
