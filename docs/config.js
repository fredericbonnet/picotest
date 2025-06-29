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
  const divId = "mermaid-" + mermaidId;
  const svgId = "mermaid-svg-" + mermaidId;
  mermaidId++;
  const div = document.createElement("div");
  div.id = divId;
  div.className = "mermaid";
  div.innerHTML = "Rendering...";
  mermaid.render(svgId, code).then((rendered) => {
    const div = document.getElementById(divId);
    div.innerHTML = rendered.svg;

    // Convert SVG links to docsify format
    const div2 = document.createElement("div");
    div.querySelectorAll("a .clickable").forEach((clickable) => {
      const a = clickable.parentElement;
      div2.innerHTML = link(a.getAttribute("xlink:href"));
      a.setAttribute("xlink:href", div2.firstChild.getAttribute("href"));
    });
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
