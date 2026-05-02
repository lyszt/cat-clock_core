# Providentia — Cat Pomodoro Clock

## Concept

A physical pomodoro timer with a cat personality. Targets the desk aesthetic market rather than the utility market. The distinction matters because it determines pricing, positioning, and who buys it — not just what it does.

---

## Market Context

### The existing competition

Generic digital timers manufactured at scale in Shenzhen. 7-segment displays, injection-molded plastic, R$15–30. They compete on price and volume. Margin per unit is thin. Winning in that space requires factory-scale output.

### Why we're not competing there

A 7-segment display puts the product in the same visual category as a kitchen timer regardless of what it does internally. The price ceiling in that category is around R$30. There is no path to R$99 from there.

### Target category

Desk accessories for students and young professionals — the same audience that buys mechanical keyboards, aesthetic desk mats, and cable management kits. This is a documented and active niche, though we haven't yet validated whether a pomodoro clock specifically fits their purchasing behavior. That's an open question.

| | Generic Competitor | This Product |
|---|---|---|
| Display | 7-segment | 16x2 LCD |
| Sound | Buzzer beep | Original music + meow |
| Category | Kitchen utility | Desk accessory |
| Price | R$15–30 | R$99 (target) |

---

## Pricing & Margin

Target price: R$99  
Estimated BOM (Arduino Nano-based): R$54–64  
Estimated gross margin: 35–45% per unit

This is viable for small-batch handmade production. It does not account for time, packaging, or shipping. Those need to be mapped before any real margin number can be claimed.

---

## Product Differentiators

These are the things that justify the price difference over a generic timer. They are also the things that require actual craft to execute well, which is a barrier a factory won't bother with.

**Sound design.** Three original compositions for UI events, plus a randomized meow that fires at every pomodoro break transition. All non-blocking — the clock doesn't freeze to play audio. Sounds were composed specifically for this product, not borrowed.

**16x2 LCD with custom sprites.** The display can show cat faces, coffee cups, session indicators. Not implemented yet — this is still on the roadmap and is one of the most important remaining pieces.

**Pomodoro logic.** 25-minute work sessions alternating with configurable breaks. The meow marks the transition. The device has three modes: off, stopwatch, and pomodoro.

---

## Sound Design

### The meow

Fires at pomodoro break transitions (work→break and break→work). Generated mathematically using a sine curve — pitch and duration vary randomly on each call. It's a personality detail, not a marketing hook.

### UI compositions

Three original pieces composed in BeepBox, translated to note arrays on the device. Non-blocking playback via a melody player that runs alongside the clock without interrupting it.

| Event | Notes | BPM |
|---|---|---|
| Power on | A3 A3 C5 A3 — G3 C5 G3 | 100 |
| Power off | D3 E3 E3 D3 C3 C3 | 100 |
| Mode switch | E3 B3 | 100 |

A 220Ω resistor in series with the buzzer reduces volume to a comfortable level.

---

## What's Left Before This Is a Product

### Required

- [ ] Custom LCD character sprites — cat face, coffee cup, session indicator
- [ ] Visual distinction between work and break sessions on the LCD
- [ ] Second button — start/stop separate from mode toggle
- [ ] Enclosure — needs to look intentional, not prototyped
- [ ] Swap Arduino Mega (current dev board) → Nano for production BOM

### Open questions

- [ ] Is there actual purchase intent in the target audience? Needs validation before investing in enclosure tooling
- [ ] Custom PCB vs perfboard for first batch — JLCPCB small runs are cheap enough to test early
- [ ] Packaging — unboxing experience matters in this market segment
- [ ] Injection mold only makes sense at volume; 3D print for first batch

---

## Distribution Strategy — Local Retail (Chapecó)

### The model

Consignment. Offer free batches to local variety shops — they display the product and only pay per unit sold. Zero upfront risk for the retailer. This eliminates e-commerce setup, shipping logistics, and the need for an established online audience before the first sale.

### Benefits

- No barrier to yes for the shop owner — they risk nothing
- Physical discovery: customers who would never find the product online walk past it in a store
- Fast feedback loop — if a batch doesn't move, you find out quickly and locally
- No shipping infrastructure needed for the initial phase
- A shop that sells consistently becomes a long-term distribution point

### What we lose

- **Margin.** Consignment shops typically take 30–40% on sale. At R$99 with a 40% cut, the take-home is R$59.40 against a BOM of R$54–64. That's breakeven or negative. The retail price likely needs to be R$120–130, or the arrangement should be a flat per-unit fee rather than a percentage. This needs to be resolved before approaching anyone.
- **Presentation control.** The shop decides placement. If it ends up next to unrelated products, the aesthetic context that justifies the price disappears.
- **Customer data.** No email, no follow-up, no direct feedback on who bought and why.
- **Cash flow.** Payment only comes when units sell — BOM is fronted with no guaranteed timeline.

### Where to look in Chapecó

Papelaria with a design or gift section, concept stores, gift shops, any shop already carrying kawaii or desk aesthetic items. Cafes with retail corners are worth considering — the target audience frequents them.

### First contact — email, not in person

Cold email keeps pressure low and gives the shop owner time to consider without feeling put on the spot. Keep it short.

> **Subject:** Produto local — sem risco para sua loja
>
> Olá [nome],
>
> Sou um maker local de Chapecó. Desenvolvi um acessório de mesa — um timer pomodoro temático de gato com display LCD e sons originais — voltado para estudantes e pessoas que cuidam do visual do espaço de trabalho.
>
> Estou procurando algumas lojas locais para trabalhar em consignação. Você ficaria com uma pequena quantidade para expor e pagaria apenas pelo que vender. Sem compromisso inicial.
>
> Posso mandar fotos ou passar com uma amostra se tiver interesse.
>
> [seu nome]

One ask. No attachments on first contact. No pricing in the opener.

---

## Marketing Hypothesis

Short-form video is the likely acquisition channel if online sales become part of the strategy. Whether that holds needs to be tested, not assumed. The product has to be finished and photographed well before any content strategy is worth planning.
