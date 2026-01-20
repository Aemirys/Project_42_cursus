<?php
session_start();

require_once dirname(__DIR__) . '/src/utils/filesystem.php';
ensure_directories();

$page = 'camera';

require_once '../src/utils/auth.php';
require_login();

require_once '../src/utils/db.php';
$pdo = get_db();

require_once '../src/utils/csrf.php';
$csrf = csrf_token();

$stmt = $pdo->prepare("
    SELECT filename, thumb, created_at
    FROM images
    WHERE user_id = ?
    ORDER BY created_at DESC
    LIMIT 12
");
$stmt->execute([$_SESSION['user_id']]);
$my_images = $stmt->fetchAll();

include '../src/views/header.php';
?>

<h1>Caméra 🎥</h1>

<?php if (!empty($_SESSION['error'])): ?>
    <p class="error"><?= htmlspecialchars($_SESSION['error']) ?></p>
    <?php unset($_SESSION['error']); ?>
<?php endif; ?>

<?php if (!empty($_SESSION['success'])): ?>
    <p class="success"><?= htmlspecialchars($_SESSION['success']) ?></p>
    <?php unset($_SESSION['success']); ?>
<?php endif; ?>

<p id="upload-error" class="error" style="display:none;"></p>

<div class="camera-layout">

<section class="camera-main">
<div class="camera-container">

    <video id="video" autoplay playsinline hidden></video>
    <canvas id="canvas"></canvas>

    <!-- FILTRES -->
    <div class="filters">
        <?php foreach (['balloon','glasses','house','knot'] as $f): ?>
            <label>
                <input type="radio" name="filter" value="<?= $f ?>.png">
                <img src="/filters/<?= $f ?>.png" alt="">
            </label>
        <?php endforeach; ?>

        <label class="filter-none">
            <input type="radio" name="filter" value="">
            <span>✖</span> Aucun
        </label>
    </div>

    <!-- CONTROLES -->
    <div class="controls">
        <button id="snap" type="button" disabled>📸 Prendre la photo</button>
        <button id="reset" type="button" disabled>❌ Annuler</button>
    </div>

    <!-- FORM -->
    <form method="POST" action="save_image.php" enctype="multipart/form-data">
        <input type="hidden" name="csrf" value="<?= htmlspecialchars($csrf) ?>">

        <input type="hidden" name="image_data" id="image_data">
        <input type="hidden" name="filter" id="filter_name">
        <input type="hidden" name="fx" id="fx">
        <input type="hidden" name="fy" id="fy">
        <input type="hidden" name="fscale" id="fscale">

        <p><strong>Pas de webcam ? Upload une image :</strong></p>
        <input type="file" name="upload_image" id="upload_image" accept="image/png,image/jpeg">

        <button type="submit" id="save-btn" disabled>💾 Enregistrer</button>
    </form>

</div>
</section>

<aside class="camera-side">
    <h3>Mes photos</h3>
    <div class="thumbs">
        <?php foreach ($my_images as $img): ?>
            <img src="/thumbs/<?= htmlspecialchars($img['thumb']) ?>" alt="">
        <?php endforeach; ?>
    </div>
</aside>

</div>

<script>
const canvas = document.getElementById('canvas');
const ctx = canvas.getContext('2d');
const video = document.getElementById('video');

const snapBtn = document.getElementById('snap');
const resetBtn = document.getElementById('reset');
const saveBtn = document.getElementById('save-btn');

const imageInput = document.getElementById('image_data');
const uploadInput = document.getElementById('upload_image');
const filterInput = document.getElementById('filter_name');
const fxInput = document.getElementById('fx');
const fyInput = document.getElementById('fy');
const fscaleInput = document.getElementById('fscale');

const uploadError = document.getElementById('upload-error');

let baseImage = null;
let filterImg = null;
let selectedFilter = null;
let dragging = false;
let frozen = false;
let animationId = null;

let filter = { x: 100, y: 100, scale: 0.35 };

/* ===================== HELPERS ===================== */
function showUploadError(msg) {
    if (!uploadError) return;
    uploadError.textContent = msg;
    uploadError.style.display = 'block';
}
function clearUploadError() {
    if (!uploadError) return;
    uploadError.textContent = '';
    uploadError.style.display = 'none';
}

/* ===================== COORDONNÉES ===================== */
function getMousePos(e) {
    const rect = canvas.getBoundingClientRect();
    return {
        x: (e.clientX - rect.left) * (canvas.width / rect.width),
        y: (e.clientY - rect.top) * (canvas.height / rect.height)
    };
}

/* ===================== WEBCAM ===================== */
navigator.mediaDevices.getUserMedia({ video: true })
.then(stream => {
    video.srcObject = stream;
    video.onloadedmetadata = () => {
        canvas.width = video.videoWidth || 640;
        canvas.height = video.videoHeight || 480;
        render();
    };
})
.catch(() => {
    showUploadError("Webcam indisponible. Utilise l'upload d'image.");
});

/* ===================== FILTRES ===================== */
document.querySelectorAll('input[name="filter"]').forEach(radio => {
    radio.addEventListener('change', () => {
        selectedFilter = radio.value || null;
        filterInput.value = selectedFilter || '';

        if (!selectedFilter) {
            filterImg = null;
            snapBtn.disabled = true;
            return;
        }

        filterImg = new Image();
        filterImg.onload = () => {
            filter.scale = 0.35;

            const w = canvas.width * filter.scale;
            const h = filterImg.height * (w / filterImg.width);

            filter.x = canvas.width / 2 - w / 2;
            filter.y = canvas.height / 4;

            snapBtn.disabled = !(baseImage || video.srcObject);
        };
        filterImg.onerror = () => {
            showUploadError("Impossible de charger le filtre.");
            filterImg = null;
            snapBtn.disabled = true;
        };
        filterImg.src = '/filters/' + selectedFilter;
    });
});

/* ===================== RENDER ===================== */
function render() {
    if (frozen) return;

    ctx.clearRect(0, 0, canvas.width, canvas.height);

    if (baseImage) {
        ctx.drawImage(baseImage, 0, 0, canvas.width, canvas.height);
    } else {
        ctx.drawImage(video, 0, 0, canvas.width, canvas.height);
    }

    if (filterImg && filterImg.complete) {
        const w = canvas.width * filter.scale;
        const h = filterImg.height * (w / filterImg.width);
        ctx.drawImage(filterImg, filter.x, filter.y, w, h);
    }

    animationId = requestAnimationFrame(render);
}

/* ===================== DRAG ===================== */
canvas.addEventListener('mousedown', e => {
    if (!filterImg) return;
    const pos = getMousePos(e);
    const w = canvas.width * filter.scale;
    const h = filterImg.height * (w / filterImg.width);

    if (pos.x >= filter.x && pos.x <= filter.x + w &&
        pos.y >= filter.y && pos.y <= filter.y + h) {
        dragging = true;
    }
});

canvas.addEventListener('mousemove', e => {
    if (!dragging || !filterImg) return;
    const pos = getMousePos(e);
    const w = canvas.width * filter.scale;
    const h = filterImg.height * (w / filterImg.width);
    filter.x = pos.x - w / 2;
    filter.y = pos.y - h / 2;
});

canvas.addEventListener('mouseup', () => dragging = false);
canvas.addEventListener('mouseleave', () => dragging = false);

/* ===================== ZOOM ===================== */
canvas.addEventListener('wheel', e => {
    if (!filterImg || !filterImg.complete) return;
    e.preventDefault();

    const oldScale = filter.scale;
    const delta = e.deltaY < 0 ? 0.05 : -0.05;
    const newScale = Math.min(1.2, Math.max(0.1, oldScale + delta));
    if (newScale === oldScale) return;

    const oldW = canvas.width * oldScale;
    const oldH = filterImg.height * (oldW / filterImg.width);
    const newW = canvas.width * newScale;
    const newH = filterImg.height * (newW / filterImg.width);

    const cx = filter.x + oldW / 2;
    const cy = filter.y + oldH / 2;

    filter.x = cx - newW / 2;
    filter.y = cy - newH / 2;
    filter.scale = newScale;
}, { passive: false });

/* ===================== SNAP ===================== */
snapBtn.addEventListener('click', () => {
    if (!filterImg || !filterImg.complete) return;

    frozen = true;
    cancelAnimationFrame(animationId);

    const raw = document.createElement('canvas');
    raw.width = canvas.width;
    raw.height = canvas.height;
    const rctx = raw.getContext('2d');

    if (baseImage) {
        rctx.drawImage(baseImage, 0, 0, raw.width, raw.height);
    } else {
        rctx.drawImage(video, 0, 0, raw.width, raw.height);
    }

    imageInput.value = raw.toDataURL('image/jpeg', 0.85);

    // Coordonnées CENTRE du sticker
    const stickerW = canvas.width * filter.scale;
    const stickerH = filterImg.height * (stickerW / filterImg.width);

    const centerX = filter.x + stickerW / 2;
    const centerY = filter.y + stickerH / 2;

    fxInput.value = (centerX / canvas.width).toFixed(6);
    fyInput.value = (centerY / canvas.height).toFixed(6);
    fscaleInput.value = filter.scale.toFixed(6);

    saveBtn.disabled = false;
    resetBtn.disabled = false;
});

/* ===================== UPLOAD (avec message d'erreur) ===================== */
uploadInput.addEventListener('change', () => {
    clearUploadError();

    const file = uploadInput.files[0];
    if (!file) return;

    if (!/^(image\/png|image\/jpeg)$/.test(file.type)) {
        showUploadError("Fichier invalide : PNG ou JPG uniquement.");
        uploadInput.value = '';
        return;
    }

    if (file.size > 5 * 1024 * 1024) {
        showUploadError("Fichier trop lourd (max 5 Mo).");
        uploadInput.value = '';
        return;
    }

    const reader = new FileReader();

    reader.onerror = () => {
        showUploadError("Impossible de lire le fichier.");
        uploadInput.value = '';
    };

    reader.onload = () => {
        const img = new Image();

        img.onerror = () => {
            showUploadError("Le fichier sélectionné n'est pas une image valide.");
            uploadInput.value = '';
            baseImage = null;
            snapBtn.disabled = true;
            saveBtn.disabled = true;
        };

        img.onload = () => {
            baseImage = img;
            canvas.width = img.width;
            canvas.height = img.height;
            frozen = false;
            render();

            snapBtn.disabled = !selectedFilter;
            saveBtn.disabled = true;
            resetBtn.disabled = false;
        };

        img.src = reader.result;
    };

    reader.readAsDataURL(file);
});

/* ===================== RESET ===================== */
resetBtn.addEventListener('click', () => {
    frozen = false;
    dragging = false;

    baseImage = null;
    filterImg = null;
    selectedFilter = null;

    document.querySelectorAll('input[name="filter"]').forEach(r => {
        r.checked = false;
    });

    imageInput.value = '';
    filterInput.value = '';
    fxInput.value = '';
    fyInput.value = '';
    fscaleInput.value = '';

    uploadInput.value = '';
    clearUploadError();

    snapBtn.disabled = true;
    saveBtn.disabled = true;
    resetBtn.disabled = true;

    cancelAnimationFrame(animationId);
    render();
});
</script>

<?php include '../src/views/footer.php'; ?>
